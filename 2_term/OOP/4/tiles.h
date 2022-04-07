#ifndef TILES_H
#define TILES_H

#include <direction.h>

#define EMPTY_TILE 0b00
#define SNAKE_TILE 0b01
#define FRUIT_TILE 0b10
#define WALL_TILE 0b11

typedef unsigned char tiletype;

#define DIRECTION_MASK 0b11100
#define TILE_TYPE_MASK 0b11

/* tile bit layout is as follows
 * 0: 2 bits - tile type
 * 2: 3 bits - next snake tile (if applicable)
 */
typedef unsigned char tile;

tile createSnakeHeadTile(direction nextTileDirection);
tile createSnakeBodyTile(direction nextTileDirection);
tile createSnakeTailTile();

inline tiletype getTileType(tile t) { return t & TILE_TYPE_MASK; }

inline tile createFruitTile() { return FRUIT_TILE; }
inline tile createEmptyTile() { return EMPTY_TILE; }

inline tile convertHeadToBodyTile(tile t) { return t; }

inline bool isEmpty(tile t) { return (t & TILE_TYPE_MASK) == EMPTY_TILE; }
inline bool isSnake(tile t) { return (t & TILE_TYPE_MASK) == SNAKE_TILE; }
inline bool isSnakeTail(tile t) {
  return isSnake(t) && ((t & DIRECTION_MASK) == NO_DIRECTION);
}
inline bool isWallTile(tile t) { return (t & TILE_TYPE_MASK) == WALL_TILE; }

inline direction getDirection(tile t) { return (t & DIRECTION_MASK) >> 2; }

enum TileType { EMPTY, SNAKE_BODY, FRUIT, WALL };

#endif  // TILES_H
