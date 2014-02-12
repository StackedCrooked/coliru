#include <iostream>
#include <string>
#include <tuple>

template<typename ReturnType, typename... Args>
class API
{
public:
    ReturnType operator()(Args... args)
    {
       // Capture args in a tuple
       auto&& t = std::forward_as_tuple(args...);
       // Get argument 0
       std::cout << std::get<0>(t) << '\n';
       // Get argument 1
       std::cout << std::get<1>(t) << '\n';
       // Get argument 2
       std::cout << std::get<2>(t) << '\n';
    }
};

int main() {
    API<void, int, const char*, std::string> api;
    api(42, "foo", "bar");
}
