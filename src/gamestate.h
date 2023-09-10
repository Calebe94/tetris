enum class GameState {
    MENU,
    GAME,
    PAUSED,
    SETTINGS,
    // Add more states as needed
    GAME_OVER,
    EXIT
};

class GameStateManager {
private:
    GameState currentState;

public:
    GameStateManager();

    void transitionTo(GameState nextState);

    GameState getCurrentState() const;

    // Static function to access the Singleton instance
    static GameStateManager& getInstance() {
        static GameStateManager instance;
        return instance;
    }

   // Delete copy constructor and assignment operator to enforce Singleton pattern
    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator=(const GameStateManager&) = delete;
};
