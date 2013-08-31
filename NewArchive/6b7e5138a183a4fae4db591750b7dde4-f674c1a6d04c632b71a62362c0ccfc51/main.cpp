#include <iostream>

template<class deleter_t>
class Example {
    private:
        deleter_t deleter;
        
    public:
        Example(deleter_t d) : deleter(d) {
            std::cout << "Making example\n";
        }
        ~Example() {
            deleter();
        }
};

class StatefulDeleter {
    private:
        int test;
        
    public:
        StatefulDeleter() : test(20) {
            
        }
        void operator()() {
            std::cout << "Deleting! State! " << test << "\n";
        }
};

int main() {
    StatefulDeleter d;
    Example<StatefulDeleter> test(d);
    return 0;
}