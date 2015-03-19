#include <iostream>
struct bob
{
    int i =8; /* how cool is this? :) If you also provide mem-initializer in the constructor, mem-initializer takes precedence
             However, this makes it really easy to specify defaults for members, and makes it less likely you 
             will forget to initialize a member when you add a new constructor. */
};
void encrypt(bob b) = delete;
int main()
{
    bob b;
    std::cout << b.i;
   // encrypt (b); // fails to compile because the function is deleted
}