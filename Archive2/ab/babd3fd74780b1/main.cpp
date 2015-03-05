#include <iostream>
#include <string>
using namespace std;

namespace xyz{
    template<class T>   
    struct TemplateClass{
        typedef std::string (*ParameterlessFunctionPointer)();
    };
}

int main()
{
    xyz::TemplateClass<int>::ParameterlessFunctionPointer func = nullptr;
    return 0;
}