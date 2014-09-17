#include <iostream>
#include <tuple>

class Record1;
class Record2;

class Record1: public std::tuple<int, Record2*> { using base = std::tuple<int, Record2*>; using base::base; };
class Record2: public std::tuple<int, Record1*> { using base = std::tuple<int, Record1*>; using base::base; };

int main() 
{
    Record1 r1 = std::make_tuple(0, nullptr);        
    std::cout << (std::get<0>(r1) == 0) << (std::get<1>(r1) == nullptr);
}
