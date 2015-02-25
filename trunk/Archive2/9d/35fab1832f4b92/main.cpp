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

int main()
{
char v = 'x'; // Simple.
char * p = & v; // Works, No issue here.
const char * cp = &v; // Works. No problem yet.
cp = p; // Works fine
char ** pp = &p; // Still ok.
const char ** cpp = &p; // HUGE HORRIFYING BARF

    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
