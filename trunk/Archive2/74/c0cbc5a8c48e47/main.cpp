#include <iostream>
#include <string>
#include <vector>

enum class Traffic_light { 
    green, 
    yellow, 
    red
};

Traffic_light & operator++(Traffic_light & t) {
    switch (t) {
        case Traffic_light::green:
            t = Traffic_light::yellow;
        break;
        case Traffic_light::yellow:
            t = Traffic_light::red;
        break;
        case Traffic_light::red:
            t = Traffic_light::green;
        break;
    }
    return t;
}

std::ostream& operator<<(std::ostream& os, Traffic_light & t)
{
    switch(t)
    {
        case Traffic_light::green:
            os << "green";
        break;
        case Traffic_light::yellow:
            os << "yellow";
        break;
        case Traffic_light::red:
            os << "red";
        break;
    }
    return os;

}

int main()
{
    Traffic_light light = Traffic_light::red;

    std::cout << "Ligth:" << ++light << std::endl;
    std::cout << "Ligth:" << ++light << std::endl;
    std::cout << "Ligth:" << ++light << std::endl;
    
    return 0;
}
