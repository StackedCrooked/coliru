#include <limits>
#include <vector>

template <typename C, typename T = typename C::value_type>
  std::vector<unsigned> histogram(C const& container)
{
    std::vector<unsigned> result(std::numeric_limits<T>::max() - std::numeric_limits<T>::min());
    for(auto& el : container)
        result[el - std::numeric_limits<T>::min()]++;

    return result;
}

// for very large char types, consider
#include <map>

template <typename C, typename T = typename C::value_type>
  std::map<T, unsigned> histogram_ex(C const& container)
{
    std::map<T, unsigned> result;

    for(auto& el : container)
        result[el]++;

    return result;
}

#include <algorithm>
#include <string>
#include <iostream>

int main()
{
     auto v = histogram   (std::string ("hello world"));
     auto m = histogram_ex(std::wstring(L"hello world"));

     std::wcout << L"Sum of frequencies: " << std::accumulate(v.begin(), v.end(), 0) << "\n";

     for (auto p : m)
         std::wcout << L"'" << p.first << L"': " << p.second << L'\n';
}
