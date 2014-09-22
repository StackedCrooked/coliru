#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct State;

struct FlyweightStates {
    static std::unordered_map<std::string, std::shared_ptr<State>> prototypes;
    static void insertPrototype (const std::string& tag, State* state) {
        prototypes.emplace(tag, std::shared_ptr<State>(state));
        std::cout << tag << " inserted in FlyweightStates::prototypes." << std::endl;
    }
};
std::unordered_map<std::string, std::shared_ptr<State>> FlyweightStates::prototypes;

struct State {
    virtual ~State() {std::cout << "State destructor called." << this << std::endl; char ch; std::cin >> ch;}
    State (const std::string& name) {
        FlyweightStates::insertPrototype(name, this);
    }
};

struct Sleeping : public State {
    static Sleeping prototype;
    Sleeping() : State("Sleeping") {}
};
Sleeping Sleeping::prototype;

int main() { }