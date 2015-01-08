#include <iostream>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
    std::vector<int>::const_iterator iter = vec.begin();
    for (; iter != vec.end(); ++iter)
    {
        os << *iter << ' ';
    }
    return os;
}
class obj
{
    public:
    obj(int x): mX(x){ std::cout << "create " << mX <<std::endl;}
    obj(const obj& other) { mX = other.mX; std::cout << "copy " << mX << std::endl;}
    int mX;
};

//only c++11 or higher 
std::vector<obj> getAllData()
{
    std::vector<obj> data;
    data.push_back(9);
    data.push_back(33);
    data.push_back(12);
    data.push_back(54);
    std::cout << "returning" << std::endl;
    return data;
}

int main()
{

    std::vector<obj> proba;
    proba = getAllData();
  //  std::cout << proba << std::endl;
}
