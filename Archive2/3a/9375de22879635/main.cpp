#include <stdexcept>

#define assert_invalid_argument(functioncall)\
try {\
    functioncall;\
	return false;\
} catch(std::invalid_argument& ex) {\
	return true;\
}

void fails() {
	throw std::invalid_argument("oh nein!");
}

int main() {
	assert_invalid_argument(fails());
}