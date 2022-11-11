#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setInterfaceStyle();
  int findThread(int threadId);
  void updateThreadInfo();
  void removeKilledIDs();
  // QString getTime(PROCESS_INFORMATION pi);
  QString getPriority(HANDLE handle);

 private slots:
  void on_createBtn_clicked();
  void on_suspendBtn_clicked();
  void on_resumeBtn_clicked();
  void on_killBtn_clicked();
  void on_killAllBtn_clicked();
  void on_priorBtn_clicked();
  void on_resultBtn_clicked();
  void on_refreshBtn_clicked();

 private:
  Ui::MainWindow *ui;
  int size;
  int countThread;
  std::vector<HANDLE> handles;
  std::vector<int> threadIDs, vec;
};
#endif  // MAINWINDOW_H
