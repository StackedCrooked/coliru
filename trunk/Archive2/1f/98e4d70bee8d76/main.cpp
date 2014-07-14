#include <iostream>
struct My_Class {};

template<typename USER_DATA>
class Processor
{
public:
    template <typename T>
    static void ProcessScalar(My_Class&, T&);
};


template <typename USER_DATA> template <typename T>
void Processor<USER_DATA>::ProcessScalar(My_Class &c, T &result)
{
}

int main()
{
    Processor<int> proc;
    
    My_Class mc;
    double value;
    proc.ProcessScalar(mc, value);   
}