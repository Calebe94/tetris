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
            error("SDL unable to create window! SDL Error: %s", SDL_GetError());
            success = false;
        }
    }

    if(success)
    {
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        if (mRenderer == NULL)
        {
            error("SDL unable to create renderer! SDL Error: %s", SDL_GetError());
        }
    }
    // Set render scale for high DPI displays
    const float scale{get_scale()};
    SDL_RenderSetScale(mRenderer, scale, scale);
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

SDL_Window * Graphics::getWindow()
{
    return mWindow;
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

// src/core/Core/Window.cpp
float Graphics::get_scale() const {
  int window_width{0};
  int window_height{0};
  SDL_GetWindowSize(
    mWindow,
    &window_width, &window_height
  );

  int render_output_width{0};
  int render_output_height{0};
  SDL_GetRendererOutputSize(
    mRenderer,
    &render_output_width, &render_output_height
  );

  const auto scale_x{
    static_cast<float>(render_output_width) /
      static_cast<float>(window_width)
  };

  return scale_x;
}
