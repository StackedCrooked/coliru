#include <iostream>
#include <string>

int delete_counter_1 = 0;
int delete_counter_2 = 0;

template<int& ctr>
void increment_counter() { ++ctr; }

template<void(*func)()>
class Deleter {
    public:
    ~Deleter() { func(); }
};

int main() {
    { /* Internal scope */
      Deleter<increment_counter<delete_counter_1>> a, b;
      Deleter<increment_counter<delete_counter_2>> c;
    }
    std::cout << "Counter1: " << delete_counter_1 << "; Counter2: " << delete_counter_2 << '\n';
    return 0;
}
