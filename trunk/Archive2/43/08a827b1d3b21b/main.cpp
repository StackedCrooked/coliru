#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
//#include <conio.h>

struct State;

struct FlyweightStates {
    static std::unordered_map<std::string, State*> prototypes;
    static void insertPrototype (const std::string& tag, State* state) {
        prototypes.emplace(tag, state);
        std::cout << tag << " inserted in FlyweightStates::prototypes." << std::endl;
    }
};
std::unordered_map<std::string, State*> FlyweightStates::prototypes;

struct State {
    virtual ~State() {std::cout << "State destructor called." << std::endl;  }
    State (const std::string& name) {
        FlyweightStates::insertPrototype(name, this);
    }
};

struct Sleeping : public State {
    static Sleeping prototype;
    Sleeping() : State("Sleeping") {}
};
Sleeping Sleeping::prototype;

int main() {}