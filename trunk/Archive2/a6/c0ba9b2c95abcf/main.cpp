#include <iostream>

class SomeType
{
    void initTrue()
    {
        std::cout << "true" << std::endl;
    }
    
    void initFalse()
    {
        std::cout << "false" << std::endl;
    }
    
public:
    
    template <bool C>
    struct Discrim {};
    
    SomeType( Discrim<true> ) { initTrue(); }
    SomeType( Discrim<false> ) { initFalse(); }
};

int main()
{
    const bool condition = true;
    
    SomeType st(SomeType::Discrim<condition>());
}
