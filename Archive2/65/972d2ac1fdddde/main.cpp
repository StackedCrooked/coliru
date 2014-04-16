#include <iostream>
#include <functional>
#include <list>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
 
int main()
{
    std::list<int> list = { 8,7,5,9,0,1,3,2,6,4 };
 
    std::cout << "before:     " << list << "\n";
    list.sort();
    std::cout << "ascending:  " << list << "\n";
    list.sort(std::greater<int>());
    std::cout << "descending: " << list << "\n";
}