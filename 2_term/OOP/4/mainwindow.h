#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <snake_controller.h>

#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QRgb>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct GamePalette {
  Qt::GlobalColor backgroundColor;
  Qt::GlobalColor snakeColor;
  Qt::GlobalColor wallColor;
  Qt::GlobalColor fruitColor;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void onTileUpdate(int x, int y, TileType type);
  void onGameStopped(int score);

 private:
  Ui::MainWindow *ui;
  SnakeController *gameController = nullptr;
  GamePalette *gamePalette = nullptr;

  QBrush *backgroundBrush = nullptr;
  QBrush *snakeBrush = nullptr;
  QBrush *wallBrush = nullptr;
  QBrush *fruitBrush = nullptr;

  QTableWidgetItem *cellAt(int x, int y);

  void keyPressEvent(QKeyEvent *event);

  void setUpPlayingField();
  void setUpGameController();

  void updatePalette(GamePalette *newPalette);
  QBrush *createBrush(Qt::GlobalColor color);
  void deleteBrushes();
  void deleteBrush(QBrush **brush);
};
#endif  // MAINWINDOW_H
