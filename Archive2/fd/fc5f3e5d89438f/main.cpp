#include <memory>
#include <iostream>

struct game_state {
    // these are supposed to have game contexts as parameters
    // but for simplicity, they're left out.
    virtual void update() = 0;
    virtual void render() = 0;
};

struct pause : game_state {
    virtual void update() {} // do nothing
    virtual void render() {
        std::cout << "You are paused\n";
    }
};

struct playing : game_state {
    virtual void update() {
        std::cout << "Updating the game\n";
    }
    
    virtual void render() {
        std::cout << "Playing the game\n";
    }
};

int main() {
    std::unique_ptr<game_state> x(new playing());
    
    // crappy game loop
    for(unsigned i = 0; i < 20u; ++i) {
        if(i == 15) {
            // pause game
            x.reset(new pause());
        }
        x->update();
        x->render();
    }
}