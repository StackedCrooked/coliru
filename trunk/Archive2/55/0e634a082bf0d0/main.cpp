#include <vector>
#include <iostream>

auto counter(){
    int licznik = 5;
    return [&licznik](){return ++licznik;};
}
 
int main()
{

    auto inc = counter();
    inc();
    int x = inc();
    std::cout << " " << x;

}