#include <iostream>
#include <memory>

// Non copyable object;
class bar
{
    bar(const bar&) = delete;
    bar& operator=(const bar&) = delete;
public:
    bar( int i ):_i(i){};
    int _i;
};
 
void foo(std::shared_ptr<bar> i)
{
    (*i)._i++;
}
 
int main()
{
    auto sp = std::make_shared<bar>(bar(13));
    foo(sp);
    std::cout << (*sp)._i << std::endl;
}