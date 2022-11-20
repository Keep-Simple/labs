#include "mainwindow.h"

#include <tchar.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <iostream>

#include "ui_mainwindow.h"

// semaphor and interlock practice

HANDLE sumSemaphore;

int duration;

std::vector<int> numbers;
volatile long resulting_sum = 0;

struct parameters {
  int from;
  int to;
  std::string method;
};

#define MAX_PROCS 16
#define nums_size 500000
std::array priorities = {THREAD_PRIORITY_TIME_CRITICAL, THREAD_PRIORITY_HIGHEST,
                         THREAD_PRIORITY_ABOVE_NORMAL,  THREAD_PRIORITY_NORMAL,
                         THREAD_PRIORITY_BELOW_NORMAL,  THREAD_PRIORITY_LOWEST,
                         THREAD_PRIORITY_IDLE};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  for (int i = 0; i < MAX_PROCS; i++) {
    for (int j = 0; j < 2; j++) {
      ui->table->setItem(i, j, new QTableWidgetItem);
    }
  }

  for (int i = 1; i < nums_size; i++) {
    numbers.push_back(i);
  }

  ui->priorCb->addItem("Realtime");
  ui->priorCb->addItem("High");
  ui->priorCb->addItem("Above normal");
  ui->priorCb->addItem("Normal");
  ui->priorCb->addItem("Below normal");
  ui->priorCb->addItem("Low");
  ui->priorCb->addItem("Idle");

  ui->syncCb->addItem("Semaphore");
  ui->syncCb->addItem("Atomic add");

  // Creating Semaphore
  sumSemaphore = CreateSemaphore(NULL,  // default security attributes
                                 1,     // initial count
                                 1,     // max count
                                 NULL   // unnamed
  );
}

MainWindow::~MainWindow() {
  delete ui;
  CloseHandle(sumSemaphore);
}

void MainWindow::updateThreadInfo() {
  for (unsigned long i = 0; i < MAX_PROCS; i++)
    for (unsigned long j = 0; j < 2; j++) ui->table->item(i, j)->setText(" ");
  for (unsigned long i = 0; i < handles.size(); i++) {
    QString threadID = QString::number((int)threadIDs[i]);
    ui->table->item(i, 0)->setText(threadID);
    ui->table->item(i, 1)->setText(getPriority(handles[i]));
  }
}

QString MainWindow::getPriority(HANDLE handle) {
  int priority = GetThreadPriority(handle);
  switch (priority) {
    case THREAD_PRIORITY_ABOVE_NORMAL:
      return QString("Above normal");
    case THREAD_PRIORITY_BELOW_NORMAL:
      return QString("Below normal");
    case THREAD_PRIORITY_HIGHEST:
      return QString("High");
    case THREAD_PRIORITY_IDLE:
      return QString("Idle");
    case THREAD_PRIORITY_LOWEST:
      return QString("Low");
    case THREAD_PRIORITY_NORMAL:
      return QString("Normal");
    case THREAD_PRIORITY_TIME_CRITICAL:
      return QString("Realtime");
    default:
      return QString("?");
  }
}

DWORD WINAPI countSum(LPVOID lpParam) {
  parameters *params = (parameters *)lpParam;
  // perform calculations
  int partial_sum = 0;
  for (int idx = params->from; idx < params->to; idx++) {
    partial_sum += numbers[idx];
  }

  // updated shared variable
  if (params->method == "Semaphore") {
    WaitForSingleObject(sumSemaphore, INFINITE);
    resulting_sum += partial_sum;
    ReleaseSemaphore(sumSemaphore,  // handle to semaphore
                     1,             // increase count by one
                     NULL);         // not interested in previous count
  } else {
    InterlockedExchangeAdd(&resulting_sum, partial_sum);
  }

  return 0;
}

void MainWindow::on_createBtn_clicked() {
  countThread = ui->threadCountCb->currentText().toInt();
  HANDLE pThread;
  DWORD pdwThreadID;
  parameters *params;
  std::string method = ui->syncCb->currentText().toStdString();

  int batch_size = numbers.size() / countThread;
  int bonus_size numbers.size() % countThread;
  for (int from = 0, to = batch_size; from < numbers.size();
       from = to, to = from + batch_size) {
    if (bonus_size) {
      to++;
      bonus_size--;
    }
    params = new parameters();
    params->from = from;
    params->to = to;
    params->method = method;
    pThread = CreateThread(NULL,  // default security attributes
                           0,     // default stack size
                           countSum,
                           (LPVOID)params,    // thread function arguments
                           CREATE_SUSPENDED,  // default creation flags
                           &pdwThreadID);     // receive thread identifier

    handles.push_back(pThread);
    threadIDs.push_back((int)pdwThreadID);
  }

  updateThreadInfo();
}

int MainWindow::findThread(int threadID) {
  for (int i = 0; i < threadIDs.size(); i++) {
    if (threadID == threadIDs[i]) return i;
  }
  return -1;
}

void MainWindow::on_suspendBtn_clicked() {
  int threadID = ui->txtPid->toPlainText().toInt();
  int index = findThread(threadID);

  SuspendThread(handles[index]);
}

void MainWindow::on_resumeBtn_clicked() {
  int threadID = ui->txtPid->toPlainText().toInt();
  int index = findThread(threadID);

  ResumeThread(handles[index]);
}

void MainWindow::on_killBtn_clicked() {
  int threadID = ui->txtPid->toPlainText().toInt();
  int index = findThread(threadID);

  TerminateThread(handles[index], NULL);
  CloseHandle(handles[index]);
  handles.erase(handles.begin() + index);
  threadIDs.erase(threadIDs.begin() + index);
  countThread--;
  updateThreadInfo();
}

void MainWindow::on_killAllBtn_clicked() {
  for (int i = 0; i < handles.size(); i++) {
    TerminateThread(handles[i], NULL);
    CloseHandle(handles[i]);
  }
  handles.clear();
  threadIDs.clear();
  updateThreadInfo();
}

void MainWindow::on_priorBtn_clicked() {
  int threadID = ui->txtPid->toPlainText().toInt();
  int index = findThread(threadID);

  SetThreadPriority(handles[index], priorities[ui->priorCb->currentIndex()]);
  updateThreadInfo();
}

void MainWindow::on_resultBtn_clicked() {
  const auto begin = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < handles.size(); i++) ResumeThread(handles[i]);

  // wait for threads to complete
  WaitForMultipleObjects(handles.size(), &handles[0], true, INFINITE);

  for (int i = 0; i < handles.size(); i++) CloseHandle(handles[i]);

  const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - begin);

  duration = time.count();
  ui->txtSentence->setText("Resulting Sum: " + QString::number(resulting_sum));
  resulting_sum = 0;
  ui->timeLbl->setText(QString::number(duration) + " ms");
}

void MainWindow::on_refreshBtn_clicked() { updateThreadInfo(); }
