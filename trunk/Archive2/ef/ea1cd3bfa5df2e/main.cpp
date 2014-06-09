#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/icl/interval_set.hpp>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct s1
{
    unsigned short val1;
    unsigned short val2;
    
};

struct s2
{
    unsigned short val1;
    
};

struct base
{
    virtual void test(int a, int b = 0) = 0;
    
};

struct derived : public base
{
    unsigned short val1;
    
    virtual void test(int a) {}
    
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::vector<std::string> vs;
    std::vector<int> vi;
    std::map<int, int> mi;
    std::map<std::string, std::string> ms;
    int i;
    char c;
    std::cout << words << std::endl;
    std::cout << sizeof(words) << " " << sizeof(vs) << " " << sizeof(vi) << std::endl;
    std::cout << sizeof(mi) << " " << sizeof(ms) << std::endl;
    std::cout << sizeof(i) << " " << sizeof(c) << std::endl;
    std::cout << sizeof(s1) << " " << sizeof(s2) << std::endl;

    //derived d;
    
    using namespace boost::icl;
//    interval_set<int> finished;
//    finished.add(discrete_interval<int>(5, 6));
//    finished.add(discrete_interval<int>(1, 4));

    interval_set<int> intervals;
    intervals += discrete_interval<int>(0, 1000);
    
    intervals -= discrete_interval<int>(0, 300);
    intervals -= discrete_interval<int>(500, 1000);
    
    std::cout << "Intervals left:\n";
    for (interval_set<int>::iterator it = intervals.begin(); it != intervals.end(); ++it)
        std::cout << *it << std::endl;
    
    

}
