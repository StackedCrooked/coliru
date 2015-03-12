#include <iostream>

using namespace std;

template <bool is_enabled = true>
class Aggregator {
public:
    void fun(int a) {
        funInternal(a);
    }

private:
    template<bool enabled = is_enabled>
    void funInternal(int , typename std::enable_if<enabled>::type* = 0) {
        std::cout << "Feature is enabled!" << std::endl;
    }
    
    template<bool enabled = is_enabled>
    void funInternal(int , typename std::enable_if<!enabled>::type* = 0) {
        std::cout << "Feature is disabled!" << std::endl;
    }
};

int main()
{
   Aggregator<true> a1;
   Aggregator<false> a2;

   a1.fun(5);
   a2.fun(5);

   return 0;
}