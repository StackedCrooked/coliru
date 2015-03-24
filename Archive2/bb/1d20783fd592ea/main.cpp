#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct finalize_class
{
protected:
    finalize_class(){}   
    ~finalize_class(){} 
};

#define finalclass virtual private finalize_class

struct B : finalclass
{
};

struct C : B
{
};

int main()
{
    C c;
    return 0;
}
