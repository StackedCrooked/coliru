#include <functional>
#include <iostream>

class Int {
   int val_;
public:
   Int() : val_(0) {}
   Int(int v) : val_(v) {}
   const operator int&() const { return val_; }
         operator int&()       { return val_; }
         operator int()        { return val_; }
   Int&  operator =(int i)     { val_ = v; return *this; }
};
 
int main()
{
}