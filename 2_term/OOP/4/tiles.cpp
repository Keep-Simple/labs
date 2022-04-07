#include "tiles.h"

tile createSnakeHeadTile(direction directionToNextTile)
{
    return createSnakeBodyTile(directionToNextTile);
}

tile createSnakeBodyTile(direction directionToNextTile)
{
    return (directionToNextTile << 2) | SNAKE_TILE;
}

tile createSnakeTailTile()
{
    return SNAKE_TILE;
}
