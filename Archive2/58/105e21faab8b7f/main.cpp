#include <iostream>

void f1(int) {}
int f2() { return 0; }





template <typename Func, typename... Args>
auto wrap(Func function, Args&&... args)
{
    auto t = function(std::forward<Args>(args)...);

    // other checks

    return t;
}

int main() {
    wrap(f1, 1);
    std::cout << wrap(f2) << std::endl;

	return 0;
}