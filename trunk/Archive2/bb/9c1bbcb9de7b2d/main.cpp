#include <string>


int main()
{
    bool test1 = false;
    bool test2 = true;
    bool test3 = true;
    
    if ((test1 && test2) || !test3)
        std::cout << 'test1';
}
