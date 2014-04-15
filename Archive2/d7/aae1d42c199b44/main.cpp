#include <iostream>
#include <vector>
#include <algorithm>

class Comparators
{
public:
    bool operator()(int first, int second)
    {
        return first < second;
    }
};

int main()
{
    class ComparatorsInner : public Comparators{};

    std::vector<int> compares ;
    compares.push_back(20) ;
    compares.push_back(10) ;
    compares.push_back(30) ;

    //Uncomment out the sort below and it will not compile.
    ComparatorsInner comparatorInner;
    std::sort(compares.begin(), compares.end(), comparatorInner);

    std::vector<int>::iterator it;
    for(it = compares.begin(); it != compares.end(); ++it)
    {
        std::cout << (*it) << std::endl;
    }
}