#ifndef _COLORS_H_
#define _COLORS_H_

#include <stdint.h>

typedef enum color {
    BLACK = 0,
    CIAN,
    YELLOW,
    VIOLET,
    GREEN,
    RED,
    BLUE,
    ORANGE
} color_t;

typedef struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

inline Color
color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    Color result;
    result.r = r;
    result.g = g;
    result.b = b;
    result.a = a;
    return result;
}

const Color BASE_COLORS[] = {
    color(0x53, 0x53, 0x53, 0xFF), // black
    color(0x2D, 0x99, 0x99, 0xFF), // Cian
    color(0x99, 0x99, 0x2D, 0xFF), // yellow
    color(0x99, 0x2D, 0x99, 0xFF), // violet
    color(0x2D, 0x99, 0x51, 0xFF), // green
    color(0x99, 0x2D, 0x2D, 0xFF), // red
    color(0x2D, 0x63, 0x99, 0xFF), // blue
    color(0x99, 0x63, 0x2D, 0xFF)  // orange
};

const Color LIGHT_COLORS[] = {
    color(0x7E, 0x7E, 0x7E, 0xFF),
    color(0x44, 0xE5, 0xE5, 0xFF),
    color(0xE5, 0xE5, 0x44, 0xFF),
    color(0xE5, 0x44, 0xE5, 0xFF),
    color(0x44, 0xE5, 0x7A, 0xFF),
    color(0xE5, 0x44, 0x44, 0xFF),
    color(0x44, 0x95, 0xE5, 0xFF),
    color(0xE5, 0x95, 0x44, 0xFF)
};

const Color DARK_COLORS[] = {
    color(0x3A, 0x3A, 0x3A, 0xFF),
    color(0x1E, 0x66, 0x66, 0xFF),
    color(0x66, 0x66, 0x1E, 0xFF),
    color(0x66, 0x1E, 0x66, 0xFF),
    color(0x1E, 0x66, 0x36, 0xFF),
    color(0x66, 0x1E, 0x1E, 0xFF),
    color(0x1E, 0x42, 0x66, 0xFF),
    color(0x66, 0x42, 0x1E, 0xFF)
};

#endif
