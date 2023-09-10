#ifndef _UI_H_
#define  _UI_H_
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "imgui.h"

class TetrisUI {
public:
    TetrisUI(SDL_Window* window, SDL_Renderer* renderer);
    void Render();
    void ToggleMenu();
    void init();
    bool getQuit();
    void setQuit(bool);
    void renderPlayerScore();
    void setPlayerScore(int score);
    void setPlayerLevel(int level);
    void showGameOver();
    void settingsMenuRender();
    void displayCreditsAbout();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool showMenu;
    bool quit = false;
    int playerScore;
    int playerLevel;
};
#endif
