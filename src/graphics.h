#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

class Graphics {
    public:
        const static int SCREEN_WIDTH = 480;
        const static int SCREEN_HEIGHT = 672;
        const static int TICKS_PER_FRAME_LIMIT = 16;

        Graphics();
        bool init();

        void clear();
        void render();

         int getScreenWidth();
         int getScreenHeight();

         virtual ~Graphics();

         SDL_Renderer * getRenderer();
         SDL_Window * getWindow();

    private:
         SDL_Window *mWindow;
         SDL_Renderer * mRenderer;
         TTF_Font * mFont;
};

#endif
