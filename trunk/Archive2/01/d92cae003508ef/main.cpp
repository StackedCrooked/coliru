#include <cmath>
#include <sol.hpp>

struct Vec {
  float x, y, z;
  Vec(float x, float y, float z) : x{x}, y{y}, z{z} {}
  float length() {
    return sqrtf(x*x + y*y + z*z);
  }
  Vec normalized() {
    float invS = 1 / length();
    return {x * invS, y * invS, z * invS};
  }
};

int main () {

    sol::state lua;
	lua.open_libraries(sol::lib::base);

    {
        sol::constructors<sol::types<float, float, float>> ctor;
        sol::userdata<Vec> udata("Vec", ctor,
          "normalized", &Vec::normalized,
          "length",     &Vec::length);

        lua.set_userdata(udata);
        // userdata dies, but still usable in lua!
    }

	lua.script("v = Vec.new(1, 2, 3)\n"
	           "print(v:length())");

	lua.script("v = Vec.new(1, 2, 3)\n"
	           "print(v:normalized():length())" );
}
