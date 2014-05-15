#include <iostream>
#include <future>



int get_value() {return 17;}



int main()
{
    auto f = std::async(get_value);

    if (f.valid())
        std::cout << f.get() << std::endl;


    return 0;
}
