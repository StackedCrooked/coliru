#include <iostream>
#include <fstream>

class theClass
{
    public:
    
    theClass() {i=1;};
    unsigned long i;
};

std::fstream& operator <<(std::fstream& rwf, const theClass& OID)
{
    unsigned long ul = OID.i;
	rwf << ul;
	return rwf;
}

int main()
{
    theClass i;
    std::cout << i << std::endl;
    return 0;
}