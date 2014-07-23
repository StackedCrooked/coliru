#include <iostream>
#include <string>
#include <memory>

int* makeInt(int left, int right)
{
    return new int(left*right);
}

int main()
{
    std::auto_ptr<int> pointer1 = std::auto_ptr<int>(makeInt(4,3));
    std::auto_ptr<int> pointer2 = std::auto_ptr<int>(new int(4*3));
    std::cout << *pointer1 << " " << *pointer2;
}
