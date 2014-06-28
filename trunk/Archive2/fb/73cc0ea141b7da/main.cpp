//#include <sol.hpp>
#include <utility>

#include <iostream>

int overloaded(int x) {
    std::cout << "overloaded" << x << std::endl;
    return 3;
}

int overloaded(int x, int y) {
    std::cout << "overloaded" << x << " " << y << std::endl;
    return 7;
}

int non_overloaded(int x) {
    std::cout << " non-overloaded" << x << std::endl;
    return 11;
}

template<typename T, typename... Args>
void set_function(T&& key, Args&&... args) {
    // fails if given overloaded set: will not work with overloaded things
    set_function( std::forward<T>(key), std::forward<Args>(args)...);
}

template<typename... Fx, typename T, typename... Args>
void set_function(T&& key, Args&&... args) {
    // will work with overloaded things
}

int main () {

    //sol::state lua;
	//lua.open_libraries(sol::lib::base);

    // BOTH need to work!
    // Should match function 2
    set_function<int>("overloaded", overloaded);
    //lua.script("overloaded(1)");
    
    // Should match function 1
    set_function("non_overloaded", non_overloaded);
    //lua.script("overloaded(1)");
}
