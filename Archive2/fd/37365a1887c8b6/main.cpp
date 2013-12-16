#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int Uint;
typedef vector<Uint> TVint;
typedef vector<Uint>::const_iterator TIterator;

class Sir
{
protected:
    Uint _count;
    TVint _elements;
public:

    Sir() : _count(0) {}

    friend std::ostream& operator << (std::ostream &out, const Sir &sir)
    {
        for(size_t i = 0; i < sir._count; i++)
        {
            out<<"[" << i << "]" << "   " << sir._elements[i]<<endl;
        }
        
        return out;
    }
};

int main()
{
    Sir s;

    cout << s;

}