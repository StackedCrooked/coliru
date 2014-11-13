#include <vector>
#include <functional>

template <typename T> struct identity { using type = T; };

template <typename T>
bool and_map(std::vector<T> v, typename identity<std::function<bool(T)>>::type fn) { return {};  }

int main()
{
    std::vector<int> v;
    and_map(v, [](int cell){ return(cell != -1); });
}
