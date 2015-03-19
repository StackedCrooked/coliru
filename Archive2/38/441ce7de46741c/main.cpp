#include <iostream>
struct bob
{
    int i =8;
};
void encrypt(bob b) = delete;
int main()
{
    bob b;
    std::cout << b.i;
   // encrypt (b); // fails to compile because the function is deleted
}