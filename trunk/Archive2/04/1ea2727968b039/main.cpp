#include <iostream>
#include <memory>
 
std::weak_ptr<int> gw;
 
void f()
{
    if (auto spt = gw.lock()) { // необходимо скопировать в shared_ptr перед использованием
        std::cout << *spt << "\n";
    } else {
        std::cout << "gw is expired\n";
    }
}
 
int main()
{
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
 
        f();
    }
 
    f();
}