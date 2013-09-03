#include <functional>
#include <string>

struct target {};

namespace ae {
    struct Game {
        void stop(target*);
    };
}

template <typename T, typename U>
void connect(T* targObj, const std::string& funcName) {
    std::function<void(Args...)> newFunc = std::bind(U, targObj); //expected primary expression before ',' token
    funcMap[funcName] = newFunc;
}

int main() {
    //target* g = nullptr;
    //connect<ae::Game, &ae::Game::stop>(g, "close");
}