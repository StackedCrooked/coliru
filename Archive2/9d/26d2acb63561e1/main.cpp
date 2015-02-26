#include <functional>
#include <iostream>
#include <vector>
#include <complex>

template<typename C, typename T>
auto median_on_sorted(
    const C& vec,
    const T &accessor) -> decltype(accessor(vec[0]))
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
    std::function<double(double)> fd = [](double x){return x;};
    std::function<std::complex<int>(const std::complex<int>&)> fc = [](const std::complex<int>& x) -> std::complex<int> {return x;};
    std::vector<int> xi = {1,2,3,4,5,6};
    std::vector<double> xd = {1,2,3.5,4.5,5,6};
    std::cout << "With int vector:" << std::endl;
    std::cout << "Median with ints:       " << median_on_sorted(xi, fi) << std::endl;
    std::cout << "Median with doubles:    " << median_on_sorted(xi, fd) << std::endl;
    std::cout << "Median with complex:    " << median_on_sorted(xi, fc) << std::endl;
    std::cout << "Median with int lambda: " << median_on_sorted(xi, [](int x){return x;}) << std::endl;
    std::cout << std::endl << "With double vector:" << std::endl;
    std::cout << "Median with ints:      " << median_on_sorted(xd, fi) << std::endl;
    std::cout << "Median with doubles:   " << median_on_sorted(xd, fd) << std::endl;
    std::cout << "Median with complex:   " << median_on_sorted(xd, fc) << std::endl;
    std::cout << "Median with int lambda: " << median_on_sorted(xd, [](int x){return x;}) << std::endl;
}