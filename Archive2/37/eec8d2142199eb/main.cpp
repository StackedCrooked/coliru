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



typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Unit;
    
void setColorUnit(Unit* unit);

int main()
{

    Unit* unit = (Unit*)malloc(sizeof(Unit));
    setColorUnit(unit);
    std::cout << "Test:" <<  unit->red << std::endl;
    
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}

void setColorUnit(Unit* unit){
    unit->red = 20;
    unit->green = 20;
    unit->blue = 20;


//    printf("Normal %d\n",unit->a);
}