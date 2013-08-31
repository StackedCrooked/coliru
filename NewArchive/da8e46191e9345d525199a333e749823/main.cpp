#include <wheels/concurrency/locker_box.h++>
#include <iostream>

template<typename T>
std::ostream& operator<< (std::ostream& os, const wheels::locker_box<T> & b)
{
    for (auto & t : b.open())
    {
        os << t;
    }
    return os;
}


int main()
{
    wheels::locker_box<int> box(0);
    
    std::cout << "Initial value: " << box << std::endl;
    for (auto & n : box.open())
    {
        n++;
    }
    std::cout << "After incrementing: " << box << std::endl;
}