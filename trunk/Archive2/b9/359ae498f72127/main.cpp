#include <cstdint>
#include <iostream>

class A
{
    struct B
    {
        bool operator==(const B& rhs) const
        {
            if((a == rhs.a)&&
               (b == rhs.b))
            {
                return true;
            }
            return false;
        }

        uint8_t a;
        uint8_t b;
    };

  public:
    constexpr static B b {0x61, 0x62};

};

int main() {
    std::cout << '{' << A::b.a << ',' << A::b.b << '}' << std::endl;
}