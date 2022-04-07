#include "snake_controller.h"

SnakeController::SnakeController(int fieldSize) {
  this->fieldSize = fieldSize;
  allocateField();
}

SnakeController::~SnakeController() { deleteField(); }

void SnakeController::forceFieldRedraw() {
  for (int x = 0; x < fieldSize; ++x) {
    for (int y = 0; y < fieldSize; ++y) {
      emit tileUpdateEvent(x, y, tileToEnum(field[x][y]));
    }
  }
}

inline void SnakeController::updateTileAt(int x, int y, tile newTile) {
  field[x][y] = newTile;
  emit tileUpdateEvent(x, y, tileToEnum(newTile));
}

TileType SnakeController::tileToEnum(tile t) {
  switch (t & TILE_TYPE_MASK) {
    case EMPTY_TILE:
      return EMPTY;
    case SNAKE_TILE:
      return SNAKE_BODY;
    case FRUIT_TILE:
      return FRUIT;
    case WALL_TILE:
      return WALL;
    default:
      return EMPTY;
  }
}

void SnakeController::resetGame() { updateGameState(READY_FOR_START); }

void SnakeController::startGame() {
  if (gameState() != READY_FOR_START) return;

  updateGameState(RUNNING);
}

void SnakeController::tick() {
  tiletype type = getTileTypeInFront();

  if (type == WALL_TILE || type == SNAKE_TILE) {
    updateGameState(STOPPED);
    return;
  }

  if (type == FRUIT_TILE) {
    placeFruit();
    ++snakeLength;
  } else {
    moveTail();
  }
  moveHead(newSnakeHeadDirection);

  snakeHeadDirection = newSnakeHeadDirection;
}

void SnakeController::getRandomCoordinates(int *x, int *y) {
  *x = rand() % fieldSize;
  *y = rand() % fieldSize;
}

void SnakeController::moveHead(const direction headDirection) {
  int px = snakeHeadX, py = snakeHeadY;
  moveCoordinates(&snakeHeadX, &snakeHeadY, headDirection);

  updateTileAt(px, py, convertHeadToBodyTile(field[px][py]));
  updateTileAt(snakeHeadX, snakeHeadY,
               createSnakeHeadTile(oppositeTo(headDirection)));
}

void SnakeController::moveTail() {
  int tailX = snakeHeadX, tailY = snakeHeadY;
  tile tile = field[tailX][tailY];
  int px = 0, py = 0;
  while (!isSnakeTail(tile)) {
    px = tailX;
    py = tailY;

    direction dir = getDirection(tile);
    moveCoordinates(&tailX, &tailY, dir);
    tile = field[tailX][tailY];
  }
  updateTileAt(tailX, tailY, EMPTY_TILE);
  updateTileAt(px, py, createSnakeTailTile());
}

void SnakeController::updateGameState(GameState newState) {
  this->state = newState;
  switch (newState) {
    case STOPPED:
      killTimer(timerId);
      emit gameStopEvent(snakeLength);
      break;
    case RUNNING:
      timerId = startTimer(BASE_TICK_TIME_MS / gameSpeed);
      emit gameStartEvent();
    case READY_FOR_START:
      prepareFieldForStart();
      break;
  }
}

void SnakeController::allocateField() {
  this->field = new tile *[fieldSize];
  for (int i = 0; i < fieldSize; ++i) {
    field[i] = new tile[fieldSize];
  }
}

void SnakeController::prepareFieldForStart() {
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      updateTileAt(i, j, EMPTY_TILE);
    }
  }

  // UL corner
  updateTileAt(1, 0, WALL_TILE);
  updateTileAt(0, 0, WALL_TILE);
  updateTileAt(0, 1, WALL_TILE);
  updateTileAt(1, 1, WALL_TILE);

  // UR corner
  updateTileAt(fieldSize - 1, 0, WALL_TILE);

  // LL corner
  updateTileAt(0, fieldSize - 1, WALL_TILE);
  updateTileAt(1, fieldSize - 2, WALL_TILE);

  // lines
  for (int y = 4; y < fieldSize - 4; ++y) {
    updateTileAt(3, y, WALL_TILE);
    updateTileAt(7, y + 2, WALL_TILE);
    updateTileAt(fieldSize - 4, y, WALL_TILE);
    updateTileAt(y, 1, WALL_TILE);
  }

  prepareSnake();
  placeFruit();
}

void SnakeController::prepareSnake() {
  snakeLength = INITIAL_SNAKE_LENGTH;

  snakeHeadY = snakeHeadX = fieldSize / 3;
  updateTileAt(snakeHeadX, snakeHeadY, createSnakeHeadTile(DIRECTION_LEFT));

  newSnakeHeadDirection = snakeHeadDirection = DIRECTION_RIGHT;

  for (int dx = 1; dx < INITIAL_SNAKE_LENGTH - 1; ++dx) {
    const int bodyX = snakeHeadX - dx;
    updateTileAt(bodyX, snakeHeadY, createSnakeBodyTile(DIRECTION_LEFT));
  }

  const int tailX = snakeHeadX - INITIAL_SNAKE_LENGTH + 1;
  updateTileAt(tailX, snakeHeadY, createSnakeTailTile());
}

void SnakeController::timerEvent(QTimerEvent *event) {
  if (event->timerId() != this->timerId) return;
  tick();
}

void SnakeController::setGameSpeed(int speed) {
  if (gameState() != RUNNING) {
    this->gameSpeed = speed;
  }
}

tiletype SnakeController::getTileTypeInFront() {
  int x = snakeHeadX, y = snakeHeadY;
  moveCoordinates(&x, &y, newSnakeHeadDirection);

  if (x < 0 || x >= fieldSize) return WALL_TILE;
  if (y < 0 || y >= fieldSize) return WALL_TILE;

  return getTileType(field[x][y]);
}

void SnakeController::deleteField() {
  for (int i = 0; i < fieldSize; ++i) {
    delete[] field[i];
  }
  delete[] field;
}

void SnakeController::placeFruit() {
  int x, y;
  do {
    getRandomCoordinates(&x, &y);
  } while (field[x][y] != EMPTY_TILE);
  updateTileAt(x, y, createFruitTile());
}

void SnakeController::tryChangeDirection(direction newDirection) {
  if (gameState() != RUNNING) return;

  if (!isOppositeTo(snakeHeadDirection, newDirection)) {
    newSnakeHeadDirection = newDirection;
  }
}
