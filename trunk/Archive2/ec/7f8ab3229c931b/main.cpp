#include <iostream>
#include <string>
#include <vector>

using uint=unsigned int;

class Thing
{
public:
    template<typename T>
    struct Type { static uint const index; };
};

struct ThingTypeIndex
{
    static uint counter;
};

template<typename T>
uint const Thing::Type<T>::index(ThingTypeIndex::counter++);

uint ThingTypeIndex::counter = 0;

int main()
{
    std::cout << "#: " << Thing::Type<int>::index << std::endl;
    std::cout << "#: " << Thing::Type<double>::index << std::endl;
    std::cout << "#: " << Thing::Type<char>::index << std::endl;
    
    return 0;
}
