#ifndef _TILE_H_
#define _TILE_H_
#include "SDL2/SDL.h"
#include "colors.h"

#define TILE_SIZE 32
#define GRID_SIZE 32

class Tile {
    public:
        Tile(SDL_Renderer *renderer);
        void fillRect(int x, int y, int width, int height, Color color);
        void drawRect(int x, int y, int width, int height, Color color);
        void drawCell(uint32_t row, uint32_t col, uint32_t offset_x, uint32_t offset_y, bool outline = false);

        // Setters
        void setBaseColor(const Color color);
        void setLightColor(const Color color);
        void setDarkColor(const Color color);
        void setColors(const Color base, const Color light, const Color dark);

    private:
        SDL_Renderer *renderer;
        Color base = BASE_COLORS[0];
        Color light = LIGHT_COLORS[0];
        Color dark = DARK_COLORS[0];
};
#endif
