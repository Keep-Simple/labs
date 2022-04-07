#ifndef DIRECTION_H
#define DIRECTION_H

typedef unsigned char direction;

#define NO_DIRECTION 0b000

#define DIRECTION_UP 0b100
#define DIRECTION_DOWN 0b111
#define DIRECTION_RIGHT 0b101
#define DIRECTION_LEFT 0b110

inline direction oppositeTo(direction dir) {
    return (~dir & 0b11) | 0b100;
}

inline bool isOppositeTo(direction a, direction b) {
    return a == oppositeTo(b);
}

inline void moveCoordinates(int *x, int *y, direction dir) {
    switch (dir) {
    case DIRECTION_UP:
        --(*y);
        break;
    case DIRECTION_DOWN:
        ++(*y);
        break;
    case DIRECTION_LEFT:
        --(*x);
        break;
    case DIRECTION_RIGHT:
        ++(*x);
        break;
    }
}

#endif // DIRECTION_H
