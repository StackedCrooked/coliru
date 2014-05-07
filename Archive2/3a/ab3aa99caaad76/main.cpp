#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

struct foo{
    vector<int> m_vec;
    vector<int>& getVec1()
    {
        return m_vec;
    }
    vector<int> getVec2() &
    {
        return m_vec;
    }
};
int main()
{
    foo x;
    x.m_vec.push_back(1);
    std::cout << x.getVec1().size() << std::endl;
    x.m_vec.push_back(2);
    std::cout << x.getVec2().size() << std::endl;
}
