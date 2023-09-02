#include <stdio.h>
#include "seethe.h"
#include "graphics.h"

Graphics::Graphics() :
    mWindow(NULL), mRenderer(NULL), mFont(NULL) {
}

bool Graphics::init() {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        error("SDL unable to initialize! SDL Error: %s", SDL_GetError());
        success = false;
    }

    if(TTF_Init() == -1)
    {
        error("SDL_ttf unable to initialize! SDL_ttf Error: %s", SDL_GetError());
        success = false;
        TTF_GetError();
    }

    if(success)
    {
        mWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (mWindow == NULL)
        {
            error(" SDL unable to create renderer! SDL Error: %s", SDL_GetError());
            success = false;
        }
    }

    // TODO Init (create) a Frame Timer control

    SDL_ShowCursor(0);

    return success;
}

void Graphics::clear()
{
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);
}

void Graphics::render()
{
    SDL_RenderPresent(mRenderer);
    // TODO Add a frame timer control
}


SDL_Renderer* Graphics::getRenderer()
{
    return mRenderer;
}

int Graphics::getScreenWidth()
{
    return SCREEN_WIDTH;
}

int Graphics::getScreenHeight()
{
    return SCREEN_HEIGHT;
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;

    TTF_Quit();
    SDL_Quit();
}
