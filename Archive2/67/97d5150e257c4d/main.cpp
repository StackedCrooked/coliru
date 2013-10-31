#include <iostream>
#include <string>
#include <vector>

class CFoo
{
public:
    CFoo();
    ~CFoo();

    static void fooMethod();
};

inline CFoo::CFoo()
{
}

inline CFoo::~CFoo()
{
    fooMethod();
}

void CFoo::fooMethod()
{
    std::cout << "in fooMethod" << std::endl;
}


int main()
{
    CFoo *f = new CFoo();
    delete f;
}
