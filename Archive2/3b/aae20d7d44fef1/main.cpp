#include <iostream>
#include <thread>

void thFunc() {
    std::cout << "Hi from thread\n";
}

int main() {
    std::thread th(&thFunc);
    std::cout << "Hi from main!\n";
    th.join();
    return 0;

}