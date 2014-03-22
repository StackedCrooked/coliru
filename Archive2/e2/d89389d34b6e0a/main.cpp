#include <iostream>
#include <vector>
 
class IntVector {
    std::vector<int> v;
    IntVector& operator=(IntVector); // not assignable
 public:
    void swap(IntVector& other) {
        v.swap(other.v);
    }
};
void swap(IntVector& v1, IntVector& v2) {
    v1.swap(v2);
}
 
int main()
{
    IntVector v1, v2;
//  std::swap(v1, v2); // compiler error! std::swap requires MoveAssignable
    std::iter_swap(&v1, &v2); // OK: library calls unqualified swap()
}