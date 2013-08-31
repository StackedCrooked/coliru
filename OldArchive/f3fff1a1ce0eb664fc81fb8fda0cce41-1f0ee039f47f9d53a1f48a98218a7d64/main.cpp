#include <iostream>
enum class WTF
{
  STATE_A = 1,
  STATE_B,
  STATE_C = 1
};

int main()
{
    
    if(WTF::STATE_A == WTF::STATE_B)
    {
        std::cout << "truly wtf" << std::endl;       
    }
    
    std::cout << static_cast<int>(WTF::STATE_B) << std::endl; // should be 2 not sure if standard say it should be sequential or not
    
    if(WTF::STATE_A == WTF::STATE_C)
    {
        std::cout << "weird enum dude" << std::endl;
    }
    
    return -1;
    
}
