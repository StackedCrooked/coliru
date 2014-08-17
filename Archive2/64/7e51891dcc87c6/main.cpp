#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class pose
{
    
public:

    pose():x(),y(),z()
    {
    }
    
    double x;
    double y;
    double z;
    
};

    std::ostream& operator<<(std::ostream& os, const pose & p)
    {
        int pre = 3;
        os << std::setprecision(pre);
        os << "x: " << p.x;
        os << " y: " << p.y;
        os << " z: " << p.z;
        return os;
    }

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::vector<pose> blah;
    blah.resize(10);
    auto count = 0;
    for (auto & a : blah)
    {
           a.x = static_cast<double>(count);
           a.y = a.x * 2;
           a.z = a.x * 3;
           count ++;
    }
    
    for (auto b = blah.begin(); b != blah.end(); b++)
    {
        std::cout << *b << std::endl;
    }
}
