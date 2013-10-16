#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template<typename T>
void cl(T& t) { T().swap(t); }

int main()
{
    using namespace std;
    vector<int> v = { 1, 2, 3, 4, 5 };
    cout << v.size() << endl;
    cl(v);
    cout << v.size() << endl;
    auto f = [&]() { cout << "wow" << endl; };
    f();
    f();
    f();
    
}
