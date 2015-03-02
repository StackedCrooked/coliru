#include <thread>
#include <chrono>
#include <iostream>

int main()
{

    {//works
        std::thread([](){
            std::cout << " thread running1\n";
        }).join();
    }

    {//compile but synstax error exist
        auto func = [](){
            std::cout << " thread running2\n";
        };

        std::thread(fun); //fun is not defined
    }


    {//compile, see next block for mystery compile error
        auto func = [](){
            std::cout << " thread running2\n";
        };

        std::thread tmp(func);
        tmp.join();
    }

    {//does not compile and don't know why
        auto func = [](){
            std::cout << " thread running2\n";
        };

        std::thread{func}.join(); //error C2371: 'func' : redefinition; different basic types
        
    }

    return 0;
}
