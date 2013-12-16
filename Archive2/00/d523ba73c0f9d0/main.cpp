#include <iostream>
#include <string>
#include <vector>
#include <thread>

struct Foo {
    Foo() {
        std::thread t([this]() {
            run();
        });
        
        t.join();
    }

    void run() {
        std::cout << "ran" << std::endl;   
    }
};
    

int main()
{
    Foo foo();
    
    return EXIT_SUCCESS;
}
