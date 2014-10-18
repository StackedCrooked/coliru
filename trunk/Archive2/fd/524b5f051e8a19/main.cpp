#include <type_traits>

class A
{
    char _s[6];
    
public:
    template <typename... Args,
    std::enable_if_t<sizeof...(Args) <= sizeof(_s) / sizeof(*_s), int> = 0>
    A(Args... args) : _s{ args... }
    {
    }
};

int main()
{
    A a{'a', 'b', 'c', 'd', 'e', 'f'};
}
