#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ui.h"
#include "SDL2/SDL.h"

TetrisUI::TetrisUI(SDL_Window* window, SDL_Renderer* renderer)
{
    this->window = window;
    this->renderer = renderer;
    showMenu = false; // Set the menu to initially hidden
}

void TetrisUI::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(this->window, this->renderer);
    ImGui_ImplSDLRenderer2_Init(this->renderer);
}

void TetrisUI::Render() {
    // ImGui menu code
    if (showMenu) {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Menu");

        // ImGui menu items (buttons)
        if (ImGui::Button("New Game")) {
            // Handle new game button press
        }
        if (ImGui::Button("Settings")) {
            // Handle settings button press
        }
        if (ImGui::Button("Exit")) {
            quit = true; // Exit the game
        }

        // Other ImGui menu items (e.g., settings)

        ImGui::End();

        // Render ImGui
        ImGui::Render();

        // SDL_RenderSetScale(this->renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        // SDL_SetRenderDrawColor(this->renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(this->renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    }
}

// Toggle the menu on/off
void TetrisUI::ToggleMenu() {
    showMenu = !showMenu;
}
