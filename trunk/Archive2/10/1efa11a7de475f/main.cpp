#include <stdexcept>

#ifdef NDEBUG
#define assert_invalid_argument(_Expression) ((void)0)
#else
#define assert_invalid_argument(functioncall)\
try {\
    assert((functioncall, false));/*evaluate functioncall but fire if function returns*/\
} catch(std::invalid_argument& ex) {}
#endif

//------------------------------------------------------------------------------

#include <cassert>
#include <iostream>

int divide(int num, int denom) {
	if(denom <= 0) throw std::invalid_argument("oh no!");
	return num / denom;
}

int main() {
	std::cout << "testing" << std::endl;
	assert_invalid_argument(divide(1,0));
	assert_invalid_argument(divide(1,-1));
	assert(divide(0,1) == 0);
	assert(divide(1,1) == 1);
	assert(divide(-1,1) == -1);
	assert(divide(15,5) == 3);
	assert(divide(17,5) == 3);
	assert(divide(-15,5) == -3);
	assert(divide(-17,5) == -3);
	std::cout << "all tests passed" << std::endl;
    assert_invalid_argument(divide(1,1));
}
