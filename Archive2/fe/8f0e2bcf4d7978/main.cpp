#include <vector>

template <typename T>
class A
{
public:
    static int i;
};


int main()
{    
    A<float>::i = 4;
    A<<int>::i = 3;
    
    std::cout << A<float::i << std::endl;
   return 0;
}