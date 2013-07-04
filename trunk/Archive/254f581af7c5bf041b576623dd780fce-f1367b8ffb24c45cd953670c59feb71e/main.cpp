#include <iostream>
#include <thread>

struct BigObject {
};

void fun (std::unique_ptr <BigObject> p) 
{
}

int main()
{
    std::unique_ptr <BigObject> p {new BigObject {}};
    std::thread u {fun, std::move (p)};
    u.detach ();
}