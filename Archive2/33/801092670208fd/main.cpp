#include <functional>
#include <iostream>
#include <vector>

int S(char, int&);

template<typename C, typename T>
auto median_on_sorted(
    const C& vec,
    std::function<T> accessor) -> decltype(accessor(vec[0]))
{
    const auto size = vec.size();
    if (size == 0)
    {
        return 0;
    }

    if (size % 2 == 0)
    {
        auto& l = vec[(size / 2) - 1];
        auto& r = vec[(size / 2)];
        return (accessor(l) + accessor(r)) / static_cast<decltype(accessor(vec[0]))>(2);
    }
    else
    {
        return accessor(vec[size / 2]);
    }
}

int main()
{
    std::function<int(int)> fi = [](int x){return x;};
    std::function<double(int)> fd = [](double x){return x;};
    std::vector<int> x = {1,2,3,4,5,6};
    std::cout << "For int " << median_on_sorted(x, fi) << std::endl;
    std::cout << "For double " << median_on_sorted(x, fd) << std::endl;
}
