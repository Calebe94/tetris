#include "gamestate.h"

GameStateManager::GameStateManager() : currentState(GameState::MENU) {
    // Initialize the game state manager with the MENU state as the default state
}

void GameStateManager::transitionTo(GameState nextState)
{
    currentState = nextState;
    if(currentState == GameState::PAUSED)
        paused = true;
    if(currentState == GameState::GAME)
        paused = false;
}

GameState GameStateManager::getCurrentState() const {
    return currentState;
}

bool GameStateManager::isPaused() const
{
    return paused;
}
