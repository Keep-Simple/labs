#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <direction.h>
#include <tiles.h>

#include <QObject>
#include <QTimerEvent>

#define BASE_TICK_TIME_MS 800

enum GameState { READY_FOR_START, RUNNING, STOPPED };

class SnakeController : public QObject {
  Q_OBJECT

 public:
  SnakeController(int fieldSize);
  ~SnakeController();

  GameState gameState() { return state; }

  void forceFieldRedraw();

  void snakeLeft() { tryChangeDirection(DIRECTION_LEFT); }
  void snakeRight() { tryChangeDirection(DIRECTION_RIGHT); }
  void snakeUp() { tryChangeDirection(DIRECTION_UP); }
  void snakeDown() { tryChangeDirection(DIRECTION_DOWN); }

  void resetGame();
  void startGame();

  void setGameSpeed(int speed);

 signals:
  void gameStartEvent();

  void tileUpdateEvent(int x, int y, TileType newType);

  void gameStopEvent(int score);

 private slots:
  void timerEvent(QTimerEvent *event);

 private:
  const int INITIAL_SNAKE_LENGTH = 2;

  GameState state;
  int timerId;

  int fieldSize;
  tile **field;

  int snakeHeadX;
  int snakeHeadY;
  direction snakeHeadDirection;
  direction newSnakeHeadDirection;

  int snakeLength;

  int gameSpeed = 3;

  tiletype getTileTypeInFront();

  void moveHead(direction headDirection);
  void moveTail();

  void updateGameState(GameState newState);

  void allocateField();
  void prepareFieldForStart();
  void prepareSnake();
  void deleteField();

  void placeFruit();

  void tick();
  void getRandomCoordinates(int *x, int *y);

  void tryChangeDirection(direction newDirection);

  void updateTileAt(int x, int y, tile newTile);
  TileType tileToEnum(tile t);
};

#endif  // GAMECONTROLLER_H
