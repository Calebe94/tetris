#include "seethe.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ui.h"
#include "gamestate.h"
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
    ImGuiIO& io = ImGui::GetIO();
   // this->io = ImGui::GetIO();

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
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    float buttonWidth = windowWidth * 0.5; // Button width as a fraction of the window width
    float buttonHeight = windowHeight * 0.1; // Button height as a fraction of the window height

    // Customize the ImGui style for a game menu
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Button color
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Button hover color
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Button pressed color

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetWindowPos(ImVec2(0, 0));

    // Calculate button position for horizontal centering
    float buttonX = (windowWidth - buttonWidth) / 2;
    float buttonY = (windowHeight - buttonHeight) / 2;

    // Render title centered at the top
    ImGui::SetWindowFontScale(2.5f); // Adjust font scale
    float titleWidth = ImGui::CalcTextSize("Tetris Menu").x;
    float titleX = (windowWidth - titleWidth) / 2;
    float titleY = buttonY - buttonHeight; // Adjust for spacing
    ImGui::SetCursorPos(ImVec2(titleX, titleY));
    ImGui::Text("Tetris Menu");

    // Set the cursor position for buttons
    ImGui::SetCursorPos(ImVec2(buttonX, buttonY));

    // TODO: this ui menu could be better.
    // I was very sleepy doint it, so I could implement it in a better way

    // ImGui menu items (buttons)
    if(GameStateManager::getInstance().getCurrentState() == GameState::PAUSED)
    {
        if (ImGui::Button("Continue", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Continue");
            GameStateManager::getInstance().transitionTo(GameState::GAME);
        }
        ImGui::SetCursorPos(ImVec2(buttonX, buttonY+buttonHeight+5));
        if (ImGui::Button("Settings", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Settings");
        }
        ImGui::SetCursorPos(ImVec2(buttonX, (buttonY+buttonHeight*2)+10));
        if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Exit");
            quit = true; // Exit the game
            GameStateManager::getInstance().transitionTo(GameState::EXIT);
        }
    }
    else
    {
        if (ImGui::Button("New Game", ImVec2(buttonWidth, buttonHeight)))
        {
            // Handle new game button press
            info("New Game");
            GameStateManager::getInstance().transitionTo(GameState::GAME);
        }
        ImGui::SetCursorPos(ImVec2(buttonX, buttonY+buttonHeight+5));
        if (ImGui::Button("Settings", ImVec2(buttonWidth, buttonHeight)))
        {
            // Handle settings button press
            info("Settings");
        }
        ImGui::SetCursorPos(ImVec2(buttonX, (buttonY+buttonHeight*2)+10));
        if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Exit");
            quit = true; // Exit the game
            GameStateManager::getInstance().transitionTo(GameState::EXIT);
        }
    }


    // Other ImGui menu items (e.g., settings)

    // Set the cursor position for the title
    ImGui::SetCursorPos(ImVec2(titleX, titleY));

    ImGui::End();

    // Render ImGui
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderClear(this->renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

// Toggle the menu on/off
void TetrisUI::ToggleMenu() {
    showMenu = !showMenu;
}

bool TetrisUI::getQuit()
{
    // info("%s", this->quit?"True":"False");
    return this->quit;
}

void TetrisUI::setQuit(bool quit)
{
    this->quit = quit;
}
