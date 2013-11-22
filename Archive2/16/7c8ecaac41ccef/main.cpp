#include <iostream>
#include <fstream>

std::fstream& operator <<(unsigned long& OID, std::fstream& rwf)
{
    rwf << OID;
    return rwf;
}

std::fstream& operator >>(unsigned long& OID, std::fstream& rwf)
{
    rwf >> OID;
	return rwf;
}

int main()
{
    unsigned long k=1;
    
    std::fstream f("test.txt");
   
    k << f;
    k >> f;
    
    return 0;
}