#include "mainwindow.h"

#include <tchar.h>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 4; i++) ui->table->setItem(i, j, new QTableWidgetItem);
}

MainWindow::~MainWindow() { delete ui; }

BOOL MainWindow::terminateProcess(const DWORD dwProcessId,
                                  const UINT uExitCode) {
  DWORD dwDesiredAccess = PROCESS_TERMINATE;
  BOOL bInheritHandle = FALSE;
  HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
  if (hProcess == NULL) return FALSE;

  BOOL result = TerminateProcess(hProcess, uExitCode);

  CloseHandle(hProcess);

  return result;
}

void MainWindow::terminateAll() {
  while (!procInfos.empty()) {
    PROCESS_INFORMATION curr = procInfos.at(procInfos.size() - 1);
    terminateProcess(curr.dwProcessId, 0);
    procInfos.pop_back();
  }
}

void MainWindow::createProcess(const double a, const double b,
                               const double step, const int iterCount) {
  std::string command = "C:\\Users\\N\\Desktop\\program_7.exe " +
                        std::to_string(a) + " " + std::to_string(b) + " " +
                        std::to_string(step) + " " + std::to_string(iterCount);
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  TCHAR tszCmdLine[1024] = {0};
  mbstowcs(tszCmdLine, command.c_str(), 1024);
  _tprintf(tszCmdLine);
  if (!CreateProcess(NULL, tszCmdLine, NULL, NULL, true, CREATE_NEW_CONSOLE,
                     NULL, NULL, &si, &pi)) {
    QMessageBox::warning(
        this, "Warning",
        "Could not create child process." + QString::number(GetLastError()));
    throw 1;
  }
  procInfos.push_back(pi);
}

void MainWindow::createProcesses(const int count, const double a,
                                 const double b, const int stepCount,
                                 const double iterCount) {
  double step = (b - a) / stepCount;
  double partitionSize = (b - a) / count;
  for (int i = 0; i < count; i++) {
    createProcess(a + partitionSize * i, a + partitionSize * (i + 1), step,
                  iterCount);
  }
}

QString MainWindow::getPID(PROCESS_INFORMATION pi) {
  return QString::number(pi.dwProcessId);
}

QString MainWindow::getPriority(PROCESS_INFORMATION pi) {
  HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi.dwProcessId);
  DWORD priority = GetPriorityClass(processHandle);
  CloseHandle(processHandle);
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
      return QString("WTF");
  }
}

QString MainWindow::getStatus(PROCESS_INFORMATION pi) {
  HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi.dwProcessId);
  DWORD status = WaitForSingleObject(processHandle, 0);
  QString result = "";
  switch (status) {
    case WAIT_OBJECT_0:
      result = "Terminated";
      break;
    default:
      int value = SuspendThread(processHandle);
      ResumeThread(processHandle);
      result = value == 0 ? "Running" : "Suspended";
  }
  CloseHandle(processHandle);
  return result;
}

QString MainWindow::getExecutionTime(PROCESS_INFORMATION pi) {
  long C_TIME = 0, E_TIME = 0, K_TIME = 0, U_TIME = 0;
  GetProcessTimes(pi.hProcess, (FILETIME *)&C_TIME, (FILETIME *)&E_TIME,
                  (FILETIME *)&K_TIME, (FILETIME *)&U_TIME);
  return QString::number(U_TIME * pow(10.0, -6), 'g', 10) + "ms";
}

void MainWindow::displayProcessInTable(const PROCESS_INFORMATION pi,
                                       const int index) {
  int row = index;
  ui->table->item(row, 0)->setText(getPID(pi));
  ui->table->item(row, 1)->setText(getPriority(pi));
  ui->table->item(row, 2)->setText(getStatus(pi));
  ui->table->item(row, 3)->setText(getExecutionTime(pi));
}

void MainWindow::updateTable() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 4; i++) ui->table->item(i, j)->setText("");
  for (int i = 0; i < procInfos.size(); i++) {
    displayProcessInTable(procInfos.at(i), i);
  }
}

void MainWindow::on_btnCreateProcess_clicked() {
  terminateAll();
  double a = ui->txtA->toPlainText().toDouble();
  double b = ui->txtB->toPlainText().toDouble();
  int stepCount = 100000 + ui->txtStep->toPlainText().toInt();
  int iterCount = 1000 + ui->txtIterCount->toPlainText().toInt();
  int procCount = ui->cbProcessCount->currentText().toInt();
  createProcesses(procCount, a, b, stepCount, iterCount);
  updateTable();
}
