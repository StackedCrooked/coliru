#include <type_traits>

using namespace std;

void f();

static_assert(is_same<decltype((f)), void(*)()>(), "");
static_assert(is_same<decltype(&f), void(*)()>(), "");

int main(){}
