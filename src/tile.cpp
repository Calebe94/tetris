#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "tile.h"

Tile::Tile(SDL_Renderer *renderer)
{
    if (renderer != NULL) this->renderer = renderer;
}

void Tile::fillRect(int x, int y, int width, int height, Color color)
{
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Tile::drawRect(int x, int y, int width, int height, Color color)
{
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void Tile::drawCell(uint32_t row, uint32_t col, uint32_t offset_x, uint32_t offset_y, bool outline)
{

    uint32_t edge = GRID_SIZE / 8;

    uint32_t x = col * GRID_SIZE + offset_x;
    uint32_t y = row * GRID_SIZE + offset_y;

    if (outline)
    {
        drawRect(x, y, GRID_SIZE, GRID_SIZE, this->base);
        return;
    }

    fillRect(x, y, GRID_SIZE, GRID_SIZE, this->dark);
    fillRect(x + edge, y, GRID_SIZE - edge, GRID_SIZE - edge, this->light);
    fillRect(x + edge, y + edge, GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, this->base);
}

// Setters
void Tile::setBaseColor(const Color color)
{
    this->base = color;
}

void Tile::setLightColor(const Color color)
{
    this->light = color;
}

void Tile::setDarkColor(const Color color)
{
    this->dark = color;
}

void Tile::setColors(const Color base, const Color light, const Color dark)
{
    this->base = base;
    this->light = light;
    this->dark = dark;
}
