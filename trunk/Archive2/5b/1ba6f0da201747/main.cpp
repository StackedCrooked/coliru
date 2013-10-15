#include <iostream>
#include <string>

struct swallow{
    template<class...Ts>
    swallow(Ts&&...){}
};

template<typename... T>
void print(std::ostream& o, T&&... ts)
{
    (void)swallow{(o << ts, 0)...};
    o << std::endl;
}

int main()
{
    print(std::cout, 1, "2", std::string{"3"});
}