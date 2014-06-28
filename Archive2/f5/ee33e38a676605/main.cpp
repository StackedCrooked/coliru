#include <sol.hpp>

#include <iostream>

int overloaded(int x) {
    std::cout << x << std::endl;
    return 3;
}

int overloaded(int x, int y) {
    std::cout << x << " " << y << std::endl;
    return 7;
}


template<typename T, typename... Args>
table& set_function(T&& key, Args&&... args) {
    return set_function<>(std::forward<T>(key), std::forward<Args>(args)...);
}

template<typename... Fx, typename T, typename... Args>
state& set_function(T&& key, Args&&... args) {
    global.set_function<Fx...>(std::forward<T>(key), std::forward<Args>(args)...);
    return *this;
}

int main () {

    sol::state lua;
	lua.open_libraries(sol::lib::base);

    lua.set_function<int>("overloaded", overloaded);
    lua.script("overloaded(1)");
}
