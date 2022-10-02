#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <windows.h>
#include <vector>
#include <string>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCreateProcess_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<PROCESS_INFORMATION> procInfos;
    void updateTable();
    BOOL terminateProcess(DWORD pid, UINT uExitCode);
    void createProcess(double a, double b, double step, int iterCount);
    void createProcesses(int count, double a, double b, int stepCount, double iterCount);
    void terminateAll();
    void displayProcessInTable(const PROCESS_INFORMATION pi, const int index);
    QString getExecutionTime(PROCESS_INFORMATION pi);
    QString getStatus(PROCESS_INFORMATION pi);
    QString getPriority(PROCESS_INFORMATION pi);
    QString getPID(PROCESS_INFORMATION pi);

};
#endif // MAINWINDOW_H
