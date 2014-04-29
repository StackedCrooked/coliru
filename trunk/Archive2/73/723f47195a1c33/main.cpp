#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Arr
{
public:
    Arr(){}
    Arr(Arr&){std::cout<< "Arr(Arr&)" << std::endl;}   
    Arr(const Arr&){std::cout<< "Arr(const Arr&)" << std::endl;}
    Arr(Arr&&) {std::cout << "Arr(Arr&&)" << std::endl; }
};

class Test
{
public:
    Test(Arr&& other):arr(std::forward<Arr>(other)){}
    Test(Test&& other):arr(std::forward<Test>(other).arr){}
    Arr arr;
};

int main()
{
    Arr arr;
//    Test t(arr);
    Test t(std::move(arr));
//    Test t3(t);
    Test t3(std::move(t));
}
