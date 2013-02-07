#include <cstdlib>
#include <iostream>

void foo()
{
    struct Init {
        Init() {
            std::cout << "Dit is de eerste keer!" << std::endl;
        }
    
    };
    static Init fInit;
}

int get_rand(int n)
{
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    return rand() % n;
}

int get_rand2(int n)
{
    struct Init
    {
        Init()
        {
            srand(time(0));
        }
    };
    static Init fInit; // only called once
    
    return rand() % n;
}

int main()
{
    std::cout << get_rand(100) << std::endl;
    std::cout << get_rand(100) << std::endl;
    std::cout << get_rand(100) << std::endl;
    std::cout << get_rand(100) << std::endl;
    
    std::cout << get_rand2(100) << std::endl;
    std::cout << get_rand2(100) << std::endl;
    std::cout << get_rand2(100) << std::endl;
    std::cout << get_rand2(100) << std::endl;
}

