int main()
{
    int n1 = 0;           // non-const object
    const int n2 = 0;     // const object
    int const n3 = 0;     // const object (same as n2)
    volatile int n4 = 0;  // volatile object
    const struct X {
        int n1;
        mutable int n2;
    } x = {0, 0};      // const object with mutable member
 
    n1 = 1; // ok, modifiable obejct
//  n2 = 2; // error: non-modifiable object
    n4 = 3; // ok, treated as a side-effect.
//  x.n1 = 4; // error: member of a const object is const
    x.n2 = 4; // ok, mutable member of a const object isn't const
 
    const int& r1 = n1; // reference to const bound to non-const object
//  r1 = 2; // error: attempt to modify through reference to const
    const_cast<int&>(r1) = 2; // ok, modifies n1
 
    const int& r2 = n2; // reference to const bound to const object
//  r2 = 2; // error: attempt to modify through reference to const
//  const_cast<int&>(r2) = 2; // undefined behavior: attempt to modify const object
}