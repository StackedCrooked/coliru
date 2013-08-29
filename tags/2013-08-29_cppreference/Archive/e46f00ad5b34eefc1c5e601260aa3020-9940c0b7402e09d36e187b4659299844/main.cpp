#include <iostream>
#include <string>
#include <vector>

#include <lua.h>

#include <boost/variant.hpp>

typedef boost::variant<unsigned int, signed int, double, bool, char const *> variant;

int main()
{
    lua_State *state = luaL_newstate();
    variant val1 = 5, val2 = 6U, val3 = 7., val4 = true, val5 = "plop";
    std::cout << val1 << val2 << val3 << val4 << val5 << std::endl;
}
