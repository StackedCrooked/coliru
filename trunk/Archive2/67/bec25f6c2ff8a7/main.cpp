#include <iostream>
#include <fstream>

class TheClass
{
    public:
    TheClass(){i=1;}
    unsigned long i;
};

std::fstream& operator <<(std::fstream& rwf, TheClass& OID)
{
    OID.i << rwf;
    return rwf;
}

std::fstream& operator >>(std::fstream& rwf, TheClass& OID)
{
    OID.i >> rwf;
	return rwf;
}

int main()
{
    TheClass k;
    
    std::fstream f("test.txt");
   
    k << f;
    k >> f;
    
    return 0;
}