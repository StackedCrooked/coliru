#include <iostream>
#include <fstream>

class theClass
{
    public:
    
    theClass() {i=1;};
    unsigned long i;
};


std::fstream& save (std::fstream& rwf, unsigned long& OID)
{
    unsigned long ul = OID;
    rwf << ul;
	return rwf;
}

std::fstream& operator <<(std::fstream& rwf, unsigned long& OID)
{
    rwf << OID;
    return rwf;
}

std::fstream& operator >>(std::fstream& rwf, unsigned long& OID)
{
    rwf >> OID;
	return rwf;
}

int main()
{
    unsigned long k=1;
    
    std::fstream f("test.txt");
        
    k >> f;
    k << i << std::endl;
    return 0;
}