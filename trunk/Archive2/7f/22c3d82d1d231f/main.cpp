#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define abstract =0

class state {
public:
    virtual void draw() abstract;
    virtual void update() abstract;
};

class menu : public state {
    virtual void draw() {
        std::cout << "We are currently in the menu\n";
    }
    
    virtual void update() {
        std::cout << "Updating the menu\n";
    }
};

class pause : public state {
    virtual void draw() {
        std::cout << "You are paused\n";
    }
    
    virtual void update() {
        std::cout << "You are still paused\n";
    }
};


int main(int argc, char** argv) {
    std::unique_ptr<state> current_state(new menu());
    
    while(1) {
        current_state->draw();
        current_state->update();
        
        if(argc > 1) {
            current_state = std::unique_ptr<state>(new pause());
        }
        
        current_state->draw();
        current_state->update();
        break;
    }
}