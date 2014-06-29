#include <sol.hpp>

#include <iostream>

int plop_xyz(int x, int y, std::string z) {
    std::cout << x << " " << y << " " << z << std::endl;
    return 11;
}

int overloaded(int x) {
    std::cout << x << std::endl;
    return 3;
}

int overloaded(int x, int y) {
    std::cout << x << " " << y << std::endl;
    return 7;
}

int main () {

    sol::state lua;
	lua.open_libraries(sol::lib::base);

    // decays into function pointer, copies function pointer
    lua.set_function("plop_xyz", plop_xyz);
    lua.script("x = plop_xyz(2, 6, 'hello')");

    int x = 0;
    auto foo = [&x] { x = 1; };
    // Copies
    lua.set_function("foo", foo);
    lua.script("foo()");

    // Does not copy
    lua.set_function("foo", std::ref(foo));
    lua.script("foo()");

    // copy-by-default, but is_convertible to base pointer
    auto qux = [] { std::cout << "qux!" << std::endl; };
    lua.set_function("qux", qux );
    lua.script("qux()");

    // reference, but is_convertible to base pointer
    lua.set_function("rqux", std::ref(qux) );
    lua.script("rqux()");

}
