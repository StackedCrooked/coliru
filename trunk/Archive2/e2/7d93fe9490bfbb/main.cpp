#include <iostream>
#include <type_traits>

constexpr bool condition = false; // set to false to see error

template <class... Opts>
class rqueue
{
    using off_t = std::conditional_t<condition, int, void>;
    
public:
    template <typename T = void>
    std::enable_if_t<!std::is_same<T, void>::value, off_t> start()
    {
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
