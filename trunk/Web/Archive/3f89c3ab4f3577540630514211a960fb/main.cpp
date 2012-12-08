#include <wheels/concurrency/locker_box.h++>
#include <iostream>


int main()
{
    wheels::locker_box<int> box(0);
    for (auto & n : box)
    {
        std::cout << "n: " << n << std::endl;
    }
}