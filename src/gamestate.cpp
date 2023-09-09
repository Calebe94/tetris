#include "gamestate.h"

GameStateManager::GameStateManager() : currentState(GameState::MENU) {
    // Initialize the game state manager with the MENU state as the default state
}

void GameStateManager::transitionTo(GameState nextState)
{
    currentState = nextState;
}

GameState GameStateManager::getCurrentState() const {
    return currentState;
}
