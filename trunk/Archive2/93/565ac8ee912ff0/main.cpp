#include <iostream>
#include <string>
#include <vector>

class Thingeh {
private:
public:
    Thingeh() { std::cout << "Construct!" << std::endl; }
    ~Thingeh() { std::cout << "Destruct!" << std::endl; }
    Thingeh(const Thingeh& cpy) { std::cout << "Copy!" << std::endl; }
    
    
};

std::ostream& operator << (std::ostream& os, const Thingeh& t)
{
    os << "Print!" << std::endl;
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto el : vec)
    {
        os << *el;
    }
    return os;
}

int main()
{
    std::vector<Thingeh*> vec;   
    vec.push_back(new Thingeh());
    std::cout << vec << std::endl;
}
