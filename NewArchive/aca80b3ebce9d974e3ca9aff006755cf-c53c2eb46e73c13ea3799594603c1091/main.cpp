#include <type_traits>

using namespace std;

static_assert(is_pointer<decltype(nullptr)>(), "");

int main(){}
