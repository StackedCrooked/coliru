#include <iostream>

template<typename T>
class POD {
   T val_;
public:
   POD() : val_(T()) {}
   POD(const T& v) : val_(v) {}
   operator const T&() const { return val_; }
   operator       T&()       { return val_; }
   operator       T()  const { return val_; }
   POD&  operator =(const T& v)     { val_ = v; return *this; }
};

typedef POD<int>    Int;
typedef POD<char>   Char;
typedef POD<double> Double;
// whatever

using namespace std;

int main()
{
    Int i;       cout << "init Int with zero : " << i << endl;
    int j = i;   cout << "init int with Int  : " << j << endl;
    Int l = 7;   cout << "init Int with int  : " << l << endl;
    
    Int array[20];  // Zero f***s given array initialization
    
    cout << "Array init with    : { ";
    for(Int k = 0; k < 20; ++k) { // 'Int' as 'for' counter
        cout << array[k] << " "; // 'Int' as array index
    };  cout << "}" << endl; 
    
    l = l * 2 + 5;  cout << "aritmetic          : " << l << endl; // arithmetic
    i = l;          cout << "operator=()        : " << i << endl; // arithmetic
}
