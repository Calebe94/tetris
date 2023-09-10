#include "seethe.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ui.h"
#include "gamestate.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

TetrisUI::TetrisUI(SDL_Window* window, SDL_Renderer* renderer)
{
    this->window = window;
    this->renderer = renderer;
    showMenu = false; // Set the menu to initially hidden
    this->playerScore = 0;
    this->playerLevel = 0;
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
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Text color (white)

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


    // TODO: this ui menu could be better.
    // I was very sleepy doint it, so I could implement it in a better way

    // ImGui menu items (buttons)
    if(GameStateManager::getInstance().getCurrentState() == GameState::PAUSED)
    {
        ImGui::Text("Tetris Menu");

        // Set the cursor position for buttons
        ImGui::SetCursorPos(ImVec2(buttonX, buttonY));
        if (ImGui::Button("Continue", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Continue");
            GameStateManager::getInstance().transitionTo(GameState::GAME);
        }
        ImGui::SetCursorPos(ImVec2(buttonX, buttonY+buttonHeight+5));
        if (ImGui::Button("Settings", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Settings");
            GameStateManager::getInstance().transitionTo(GameState::SETTINGS);
        }
        ImGui::SetCursorPos(ImVec2(buttonX, (buttonY+buttonHeight*2)+10));
        if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight)))
        {
            info("Exit");
            quit = true; // Exit the game
            GameStateManager::getInstance().transitionTo(GameState::EXIT);
        }
    }
    else if (GameStateManager::getInstance().getCurrentState() == GameState::MENU)
    {
        ImGui::Text("Tetris Menu");

        // Set the cursor position for buttons
        ImGui::SetCursorPos(ImVec2(buttonX, buttonY));
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
            GameStateManager::getInstance().transitionTo(GameState::SETTINGS);
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
    else if(GameStateManager::getInstance().getCurrentState() == GameState::GAME)
    {
        // Display the player's score
        float scoreX = (windowWidth - titleWidth) / 2; // Centered horizontally
        float scoreY = buttonY + buttonHeight ; // Below the buttons with padding
        ImGui::SetCursorPos(ImVec2(scoreX, scoreY));
        // ImGui::Text("Score: %d", playerScore); // Assuming playerScore is an integer representing the score
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

void TetrisUI::renderPlayerScore()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Button color
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Button hover color
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Button pressed color
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Text color (white)

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetWindowPos(ImVec2(0, 0));

    // Calculate position for score and level
    float scoreX = windowWidth * 0.77;

    // Display the score string
    ImGui::SetCursorPos(ImVec2(scoreX, windowHeight*0.08));
    ImGui::Text("Score"); // Assuming playerScore is an integer representing the score

    // Display the player's score
    ImGui::SetCursorPos(ImVec2(scoreX, windowHeight*0.13));
    ImGui::Text("%d", this->playerScore); // Assuming currentLevel is an integer representing the level

    // Display the level string
    ImGui::SetCursorPos(ImVec2(scoreX, windowHeight*0.31));
    ImGui::Text("Level"); // Assuming playerScore is an integer representing the score

    // Display the current level
    ImGui::SetCursorPos(ImVec2(scoreX, windowHeight*0.36));
    ImGui::Text("%d", this->playerLevel); // Assuming currentLevel is an integer representing the level

    // Display "next" tetromino string
    ImGui::SetCursorPos(ImVec2(scoreX, windowHeight*0.53));
    ImGui::Text("Next"); // Assuming playerScore is an integer representing the score

    ImGui::End();
    // Render ImGui
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void TetrisUI::setPlayerScore(int score)
{
    this->playerScore = score;
}

void TetrisUI::setPlayerLevel(int level)
{
    this->playerLevel = level;
}

void TetrisUI::showGameOver()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float buttonWidth = windowWidth * 0.5; // Button width as a fraction of the window width
    float buttonHeight = windowHeight * 0.1; // Button height as a fraction of the window height

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Button color
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Button hover color
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Button pressed color
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Text color (white)

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetWindowPos(ImVec2(0, 0));

    // Calculate button position for horizontal centering
    float buttonX = (windowWidth - buttonWidth) / 2;
    float buttonY = (windowHeight - buttonHeight) / 2;

    // Render title centered at the top
    ImGui::SetWindowFontScale(2.5f); // Adjust font scale
    float titleWidth = ImGui::CalcTextSize("Game Over").x;
    float titleX = (windowWidth - titleWidth) / 2;
    float titleY = buttonY - buttonHeight; // Adjust for spacing
    ImGui::SetCursorPos(ImVec2(titleX, titleY));

    ImGui::Text("Game Over!");
    ImGui::SetCursorPos(ImVec2(buttonX, buttonY));
    if (ImGui::Button("New Game", ImVec2(buttonWidth, buttonHeight)))
    {
        // Handle new game button press
        info("New Game");
        GameStateManager::getInstance().transitionTo(GameState::GAME);
    }

    ImGui::SetCursorPos(ImVec2(buttonX, (buttonY+buttonHeight)+5));
    if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight)))
    {
        info("Exit");
        quit = true; // Exit the game
        GameStateManager::getInstance().transitionTo(GameState::EXIT);
    }
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

bool showCreditsAbout = false;
bool showSettings = false;
float audioVolume = 50.0f; // Default volume, you can change this

void TetrisUI::settingsMenuRender() {
    // Check if the Settings menu should be displayed
    // if (!showSettings) {
    //     return;
    // }

    // ImGui code for the Settings menu
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float buttonWidth = windowWidth * 0.5; // Button width as a fraction of the window width
    float buttonHeight = windowHeight * 0.1; // Button height as a fraction of the window height

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Button color
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Button hover color
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Button pressed color
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Text color (white)

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetWindowPos(ImVec2(0, 0));

    // Calculate button position for horizontal centering
    float buttonX = (windowWidth - buttonWidth) / 2;
    float buttonY = (windowHeight - buttonHeight) / 2;

    // Render title centered at the top
    ImGui::SetWindowFontScale(2.5f); // Adjust font scale
    float titleWidth = ImGui::CalcTextSize("Settings").x;
    float titleX = (windowWidth - titleWidth) / 2;
    float titleY = buttonY - buttonHeight; // Adjust for spacing
    ImGui::SetCursorPos(ImVec2(titleX, titleY));

    ImGui::Text("Settings");

    // Audio volume slider
    ImGui::SetCursorPos(ImVec2(buttonX, buttonY)); // Adjust position as needed
    ImGui::Text("Audio Volume");

    // Store the original item width
    float originalItemWidth = ImGui::GetStyle().ItemInnerSpacing.x;

    // Calculate the position to center the slider
    float sliderWidth = buttonWidth; // Set the slider width to match the button width
    float sliderX = (windowWidth - sliderWidth) / 2;
    ImGui::SetCursorPos(ImVec2(sliderX, ImGui::GetCursorPosY())); // Center horizontally

    // Set the item width to match the button width
    ImGui::SetNextItemWidth(sliderWidth);

    ImGui::SliderFloat("##VolumeSlider", &audioVolume, 0.0f, 100.0f);
    Mix_Volume(-1, (int)audioVolume); // Set to max volume
    // Restore the original item width
    ImGui::SetNextItemWidth(originalItemWidth);


    // Credits and About page
    ImGui::SetCursorPos(ImVec2(buttonX, buttonY+buttonHeight + 10)); // Adjust position as needed
    if (ImGui::Button("Credits / About", ImVec2(buttonWidth, buttonHeight))) {
        // Show the Credits/About page
        showCreditsAbout = true;
        GameStateManager::getInstance().transitionTo(GameState::CREDITS);
    }

    ImGui::SetCursorPos(ImVec2(buttonX, buttonY+(buttonHeight*2)+15)); // Adjust position as needed
    if (ImGui::Button("Back to Main Menu", ImVec2(buttonWidth, buttonHeight))) {
        showSettings = false;
        showSettings = false;
        if(GameStateManager::getInstance().isPaused())
        {
            GameStateManager::getInstance().transitionTo(GameState::GAME);
        }
        else
        {
            GameStateManager::getInstance().transitionTo(GameState::MENU);
        }

        info("Return to main menu");
    }

    ImGui::End();

    // Render ImGui
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderClear(this->renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void TetrisUI::displayCreditsAbout() {
 ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float buttonWidth = windowWidth * 0.5; // Button width as a fraction of the window width
    float buttonHeight = windowHeight * 0.05; // Button height as a fraction of the window height

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Button color
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Button hover color
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Button pressed color
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Text color (white)

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetWindowPos(ImVec2(0, 0));

    // Calculate button position for horizontal centering
    float buttonX = (windowWidth - buttonWidth) / 2;
    float buttonY = (windowHeight - buttonHeight) / 2;

    // Render title centered at the top
    ImGui::SetWindowFontScale(2.5f); // Adjust font scale
    float titleWidth = ImGui::CalcTextSize("Tetris Game Credits").x;
    float titleX = (windowWidth - titleWidth) / 2;
    float titleY = buttonY - buttonHeight; // Adjust for spacing
    ImGui::SetCursorPos(ImVec2(titleX, titleY - (buttonHeight*5)));

    ImGui::Text("Tetris Game Credits");


    ImGui::SetWindowFontScale(2.0f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("Developer").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY - (buttonHeight*3)));
    ImGui::Text("Developer");

    ImGui::SetWindowFontScale(1.5f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("Edimar Calebe Castanho").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY - (buttonHeight*2)));
    ImGui::Text("Edimar Calebe Castanho");

    ImGui::SetWindowFontScale(2.0f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("Email").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY - (buttonHeight)));
    ImGui::Text("Email");

    ImGui::SetWindowFontScale(1.5f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("contato@calebe.dev.br").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY));
    ImGui::Text("contato@calebe.dev.br");

    ImGui::SetWindowFontScale(2.0f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("Website").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY + (buttonHeight)));
    ImGui::Text("Website");

    ImGui::SetWindowFontScale(1.5f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("https://calebe.dev.br").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY + (buttonHeight*2)));
    ImGui::Text("https://calebe.dev.br");

    ImGui::SetWindowFontScale(2.0f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("Repository").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY + (buttonHeight*3)));
    ImGui::Text("Repository");

    ImGui::SetWindowFontScale(1.5f); // Adjust font scale

    titleWidth = ImGui::CalcTextSize("https://github.com/Calebe94/tetris").x;
    titleX = (windowWidth - titleWidth) / 2;
    titleY = buttonY - buttonHeight;
    ImGui::SetCursorPos(ImVec2(titleX, titleY + (buttonHeight*4)));
    ImGui::Text("https://github.com/Calebe94/tetris");

    ImGui::SetCursorPos(ImVec2(buttonX, buttonY+(buttonHeight*4)+25)); // Adjust position as needed
    if (ImGui::Button("Back to Main Menu", ImVec2(buttonWidth, windowHeight * 0.1))) {
        showSettings = false;
        if(GameStateManager::getInstance().isPaused())
        {
            GameStateManager::getInstance().transitionTo(GameState::GAME);
        }
        else
        {
            GameStateManager::getInstance().transitionTo(GameState::MENU);
        }

        info("Return to main menu");
    }

    ImGui::End();
    // Render ImGui
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_RenderClear(this->renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}
