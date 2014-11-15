#include <iostream>

class Bar
{
private:
    constexpr static const char * TEST[] = {"a", "b"};
public:
    Bar(int x, int y)
    {
        for(auto & c : Bar::TEST)
        {
            std::cout << c << std::endl;   
        }
    }
};

int main(void)
{
    Bar(5,6);
}