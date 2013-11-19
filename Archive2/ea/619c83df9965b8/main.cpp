#include <stdexcept>

#ifdef NDEBUG
#define assert(_Expression) ((void)0)
#else
#define assert_invalid_argument(functioncall)\
try {\
    functioncall;\
	return false;\
} catch(std::invalid_argument& ex) {\
	return true;\
}
#endif

int divide(int num, int denom) {
    if(denom <= 0) throw std::invalid_argument("oh nein!");
    return num / denom;
}

#include <cassert>

int main() {
	assert_invalid_argument(divide(1,0));
    assert_invalid_argument(divide(1,-1));
    assert(divide(0,1) == 0);
    assert(divide(1,1) == 1);
    assert(divide(-1,1) == -1);
    assert(divide(15,5) == 3);
    assert(divide(17,5) == 3);
    assert(divide(-15,5) == -3);
    assert(divide(-17,5) == -3);
}