#include <iostream>
#include <memory>
 
std::weak_ptr<int> gw;
 
void f()
{
    if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
	std::cout << *spt << "\n";
    }
    else {
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