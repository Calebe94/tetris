#ifndef _UI_H_
#define  _UI_H_
#include "SDL2/SDL.h"
#include "imgui.h"

class TetrisUI {
public:
    TetrisUI(SDL_Window* window, SDL_Renderer* renderer);
    void Render();
    void ToggleMenu();
    void init();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool showMenu;
    bool quit;
};
#endif
