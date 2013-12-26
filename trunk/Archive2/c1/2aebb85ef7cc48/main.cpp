#include <vector>
#include <iostream>

auto counter(){
    int licznik = 5;
    return [=]()mutable{return ++licznik;};
}
 
int main()
{

    auto inc = counter();
    auto inc2 = counter();
    inc();
    int x = inc();
    
    std::cout << x <<" "<< inc2();

}