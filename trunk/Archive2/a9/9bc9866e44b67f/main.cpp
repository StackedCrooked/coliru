#include <iostream>

int main()
{
    int (*func)();
    
    int i = 0;
    func =
        [&]()->int {
            std::cout << "func(): i= " << i << std::endl;
            return 0;
        }

}