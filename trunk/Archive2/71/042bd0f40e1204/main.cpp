#include <iostream>

typedef std::function<void()> f_t;

struct no_timer_tag{};
std::ostream& operator <<(std::ostream& s,const no_timer_tag& t)
{
    return s;
}

int main()
{
    std::cout<<no_timer_tag()<<std::endl;
}
