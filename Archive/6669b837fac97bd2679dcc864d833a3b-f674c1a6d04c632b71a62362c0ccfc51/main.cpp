#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <numeric>
#include <algorithm>

using namespace std;

struct people
{
    people(string const&n, size_t a): name(n), age(a) {};
    people() : people("paul",22) {};
    string name;
    size_t age;
    size_t Age() const {return age;};
};

struct cat
{
    cat( size_t a): age(a) {};
    cat() : cat(2) {};
    size_t age;
    size_t Age() const {return age;};
};

template<typename T>
size_t average_age(T const& container)
{
    typedef typename T::value_type X;
    size_t sum_ages(0);
    for_each(begin(container),end(container),[&](X const& x){ sum_ages += x.Age();});
    return sum_ages/container.size();
}

int main()
{
    //array<people,6> somePeople;
    //vector<people> somePeople{{"thomas",10},{"thomas",8},{"thomas",45},{"thomas",10},{"thomas",33},{"thomas",22}};
    list<people> somePeople{{"thomas",10},{"thomas",18},{"thomas",45},{"thoas",10},{"thomas",33}};
    std::cout << "avg=" << average_age(somePeople) << std::endl;
    
    array<cat,8> cats;
    std::cout << "cats avg=" << average_age(cats) << std::endl;
}
