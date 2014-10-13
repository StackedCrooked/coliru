#include <iostream>
#include <type_traits>

constexpr bool condition = true; // set to false to see error

template <class... Opts>
class rqueue
{
    using off_t = std::conditional_t<condition, int, void>;
    
public:
    off_t start()
    {
        static_assert(!std::is_same<off_t, void>::value, "!");
        return start_();
    }
    
private:
    off_t start_()
    {
        std::cout << "start_()" << std::endl;
        return 1;
    }
};

int main()
{
    rqueue<> q;  
    q.start();
}
