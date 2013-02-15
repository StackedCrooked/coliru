// User header:
#include <memory>

class GameContext {

    // Interface- use Standard library to heart's content
    virtual ~GameContext() {}
};

std::unique_ptr<GameContext> __declspec(dllimport) create_game_context();


// Implementation header:
#include <memory>

class GameContext {

    // Interface- use Standard library to heart's content
    virtual ~GameContext() {}
};

class GameContextImpl : public GameContext {
    // Blah blah blah
};

std::unique_ptr<GameContext> __declspec(dllexport) create_game_context() {
    return make_unique<GameContextImpl>();
}

