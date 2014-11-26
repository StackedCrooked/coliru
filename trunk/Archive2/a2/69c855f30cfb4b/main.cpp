#include <iostream>
#include <vector>

using namespace std;

template<class T>
auto toVector()
{
    return vector<T>();
}

template<class T, size_t first, size_t... rest>
auto toVector()
{
    auto v = toVector<T, rest...>();
    v.push_back(first);
    return v;
}

int main()
{
    auto v = toVector<int, 2, 3, 4>();
    
    for (auto e : v)
        cout << e << endl;
}
