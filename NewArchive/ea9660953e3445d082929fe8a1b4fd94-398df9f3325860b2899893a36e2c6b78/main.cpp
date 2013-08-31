

template<int N>
struct Lounge
{
};


struct
{
    constexpr int operator++(int)
    {
        return 42;
    }
}C;


Lounge<C++> the_lounge;
