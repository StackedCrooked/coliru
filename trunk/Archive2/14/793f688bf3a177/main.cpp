#include <iostream>
#include <type_traits>

constexpr bool condition = true; // set to false to see error

template <bool condition, typename CRTP>
struct start_base {};

template <typename CRTP>
struct start_base<true, CRTP>
{    
    int start()
    {
        return static_cast<CRTP*>(this)->start_();
    }
};

template <class... Opts>
class rqueue : public start_base<condition, rqueue<Opts...>>
{
    friend class start_base<condition, rqueue<Opts...>>;
    
private:
    int start_()
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
