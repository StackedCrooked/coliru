#include <future>
#include <iostream>
 
int main()
{
    std::future<int> empty;
    try {
        int n = empty.get();
    } catch (const std::future_error& e) {
        std::cout << "Caught a future_error with code \"" << e.code()
                  << "\"\nMessage: \"" << e.what() << "\"\n";
    }
}