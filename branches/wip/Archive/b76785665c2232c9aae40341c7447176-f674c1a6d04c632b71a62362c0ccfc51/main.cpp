#include <iostream>
#include <vector>

int main()
{
 
    typedef const std::vector<int>& t;

    class SomeClass
    {
        t data;
    public:
        SomeClass(t _data) : data(_data) {}
        void disp()
        {
            for (auto v : data)
                std::cout << v << ", ";
        }        
    };
    
    int A = 1;
    int B = 2;
    
    SomeClass f = SomeClass( {A, B} );
    f.disp();

}
