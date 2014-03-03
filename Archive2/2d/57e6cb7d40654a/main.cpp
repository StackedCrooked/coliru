#include <iostream>

struct no_timer_tag{};
std::ostream& operator <<(std::ostream& s,const no_timer_tag& t)
{
    return s;
}

int main()
{
    std::cout<<no_timer_tag()<<std::endl;
}
