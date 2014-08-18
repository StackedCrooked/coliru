#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BigClass
{
public:
    static const int MAX_SIZE = 100;
    
    BigClass()
    {
        cout << "BigClass default constructor" << endl;
    }
    
    BigClass(const BigClass & rhs)
    {
        cout << "BigClass copy constructor" << endl;
    }
    
    ~BigClass()
    {
        cout << "BigClass destructor" << endl;
    }
    
    void incr(const int n)
    {
        ++array[n];
    }
    
    int operator[](const int n) const
    {
        return array[n];
    }
    
private:
    int array[MAX_SIZE];
};

BigClass createBigClass()
{
    return BigClass();
}

int main()
{
    const BigClass big = createBigClass();
    std::cout << "big[50] = " << big[50] << std::endl;
}
