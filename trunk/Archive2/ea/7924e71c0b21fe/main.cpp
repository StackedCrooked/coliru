#include <assert.h>

enum class color { red, green, blue };

const char* to_string(color c)
{
    switch (c)
    {
        case color::red: return "red";
        case color::green: return "blue";
        case color::blue: return "blue";
        default: assert(!"Invalid color");
    }
}


int main()
{
    to_string(color::green);
    
    to_string(static_cast<color>(123));
    
}
