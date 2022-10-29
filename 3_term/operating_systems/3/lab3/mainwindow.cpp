#include "mainwindow.h"

#include <tchar.h>

#include "ui_mainwindow.h"

std::array priorities = {REALTIME_PRIORITY_CLASS,     HIGH_PRIORITY_CLASS,
                         ABOVE_NORMAL_PRIORITY_CLASS, NORMAL_PRIORITY_CLASS,
                         BELOW_NORMAL_PRIORITY_CLASS, IDLE_PRIORITY_CLASS};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  updateTable();
}

MainWindow::~MainWindow() { delete ui; }

BOOL MainWindow::terminateProcess(const DWORD dwProcessId,
                                  const UINT uExitCode) {
  for (auto proc : procInfos) {
    if (proc.dwProcessId == dwProcessId) {
      BOOL result = TerminateProcess(proc.hProcess, uExitCode);
      CloseHandle(proc.hProcess);
      return result;
    }
  }
  QMessageBox::warning(this, "No such child PID found",
                       "Make sure you entered correct PID");
  return false;
}

void MainWindow::terminateAll() {
  while (!procInfos.empty()) {
    terminateProcess(procInfos.back().dwProcessId, 0);
    procInfos.pop_back();
  }
}

void MainWindow::createProcess(const double a, const double b,
                               const double step, const int iterCount) {
  std::string command = "Z:\\3\\program_7.exe " + std::to_string(a) + " " +
                        std::to_string(b) + " " + std::to_string(step) + " " +
                        std::to_string(iterCount);
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  TCHAR cmdLine[1024] = {0};
  mbstowcs(cmdLine, command.c_str(), 1024);
  if (!CreateProcess(NULL, cmdLine, NULL, NULL, true, CREATE_NEW_CONSOLE, NULL,
                     NULL, &si, &pi)) {
    QMessageBox::warning(
        this, "Warning",
        "Could not create child process." + QString::number(GetLastError()));
    throw 1;
  }
  procInfos.push_back(pi);
}

void MainWindow::createProcesses(int chunksCount, double a, double b,
                                 int stepCount, double iterCount) {
  auto distance = b - a;
  auto step = distance / stepCount;
  auto chunkSize = distance / chunksCount;
  iterCount /= chunksCount;
  for (int i = 0; i < chunksCount; i++)
    createProcess(a + chunkSize * i, a + chunkSize * (i + 1), step, iterCount);
}

QString MainWindow::getPID(PROCESS_INFORMATION pi) {
  return QString::number(pi.dwProcessId);
}

QString MainWindow::getPriority(PROCESS_INFORMATION pi) {
  DWORD priority = GetPriorityClass(pi.hProcess);
  switch (priority) {
    case ABOVE_NORMAL_PRIORITY_CLASS:
      return QString("Above normal");
    case BELOW_NORMAL_PRIORITY_CLASS:
      return QString("Below normal");
    case HIGH_PRIORITY_CLASS:
      return QString("High");
    case IDLE_PRIORITY_CLASS:
      return QString("Idle");
    case NORMAL_PRIORITY_CLASS:
      return QString("Normal");
    case REALTIME_PRIORITY_CLASS:
      return QString("Realtime");
    default:
      return QString("?");
  }
}

QString MainWindow::getExecutionTime(PROCESS_INFORMATION pi) {
  long C_TIME = 0, E_TIME = 0, K_TIME = 0, U_TIME = 0;
  GetProcessTimes(pi.hProcess, (FILETIME *)&C_TIME, (FILETIME *)&E_TIME,
                  (FILETIME *)&K_TIME, (FILETIME *)&U_TIME);
  return QString::number(U_TIME * pow(10.0, -3), 'g', 10) + "ms";
}

void MainWindow::displayProcessInTable(const PROCESS_INFORMATION pi,
                                       const int row) {
  ui->table->item(row, 0)->setText(getPID(pi));
  ui->table->item(row, 1)->setText(getPriority(pi));
  ui->table->item(row, 2)->setText(getExecutionTime(pi));
}

void MainWindow::updateTable() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 3; j++) ui->table->setItem(i, j, new QTableWidgetItem);

  for (auto i = 0; i != procInfos.size(); i++)
    displayProcessInTable(procInfos[i], i);
}

void MainWindow::on_btnCreateProcess_clicked() {
  terminateAll();
  double a = ui->txtA->toPlainText().toDouble();
  double b = ui->txtB->toPlainText().toDouble();
  int stepCount = 100000 + ui->txtStep->toPlainText().toInt();
  int iterCount = 10 + ui->txtIterCount->toPlainText().toInt();
  int procCount = ui->cbProcessCount->currentText().toInt();
  createProcesses(procCount, a, b, stepCount, iterCount);
  updateTable();
}

void MainWindow::on_btnGetTime_clicked() { updateTable(); }

void MainWindow::on_btnRun_clicked() {
  auto pid = ui->txtPID->toPlainText().toInt();

  for (auto proc : procInfos) {
    if (proc.dwProcessId == pid) ResumeThread(proc.hThread);
  }

  updateTable();
}

void MainWindow::on_btnSuspend_clicked() {
  auto pid = ui->txtPID->toPlainText().toInt();

  for (auto proc : procInfos) {
    if (proc.dwProcessId == pid) SuspendThread(proc.hThread);
  }

  updateTable();
}

void MainWindow::on_btnKill_clicked() {
  auto pid = ui->txtPID->toPlainText().toInt();
  terminateProcess(pid, 1);
  updateTable();
}

void MainWindow::on_btnKillAll_clicked() {
  terminateAll();
  updateTable();
}

void MainWindow::on_btnChangePriority_clicked() {
  auto pid = ui->txtPID->toPlainText().toInt();
  auto priority = ui->cbPriorityClass->currentText().toStdString();

  for (auto proc : procInfos) {
    if (proc.dwProcessId == pid)
      SetPriorityClass(proc.hProcess,
                       priorities[ui->cbPriorityClass->currentIndex()]);
  }

  updateTable();
}
