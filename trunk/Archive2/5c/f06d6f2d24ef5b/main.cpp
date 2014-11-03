#include <iostream>
#include <string>
#include <sstream>

struct someCoolClass
{
    someCoolClass(int i) : _i(i)
    {}

    friend std::ostream& operator<<(std::ostream& os, const someCoolClass& rhs)
    {
        std::ostringstream ss;
        ss.copyfmt(os);
        ss << rhs._i;
        return os << ss.str();
    }
private:
    int _i;
};

int main()
{
    someCoolClass c(10);
    std::cout << std::uppercase << std::hex << c << std::endl;
}
