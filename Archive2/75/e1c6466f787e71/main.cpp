#include <iostream>
#include <fstream>

class TheClass
{
    public:
    TheClass(){i=1;}
    unsigned long i;
};

std::fstream& operator <<(TheClass& OID, std::fstream& rwf)
{
    rwf << OID.i;
    return rwf;
}

std::fstream& operator >>(TheClass& OID, std::fstream& rwf)
{
    rwf >> OID.i;
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