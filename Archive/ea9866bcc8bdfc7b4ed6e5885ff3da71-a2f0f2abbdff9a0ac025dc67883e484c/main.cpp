#include <iostream>


struct Test
{
    Test(int & n) : n(n) {}
    
    void inc() const { n++; }
        
    int & n;
};


int main()
{
    int n = 2;
    Test test(n);
    test.inc();
    std::cout << test.n << std::endl;
}