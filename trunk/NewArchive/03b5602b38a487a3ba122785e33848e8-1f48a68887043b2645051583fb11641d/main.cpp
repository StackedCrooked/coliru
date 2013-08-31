#include <functional>

template<typename R, typename... P>
void myfunc(std::function<R(P...)> const &func) {}

int main() {
    myfunc([](){});
}
