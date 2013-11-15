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
    rwf << OID.i;
    return rwf;
}

std::fstream& operator >>(std::fstream& rwf, TheClass& OID)
{
    rwf >> OID.i;
	return rwf;
}

int main()
{
    TheClass k;
    
    std::fstream f("test.txt");
   
    f >> k;
    f << k;
    
    return 0;
}