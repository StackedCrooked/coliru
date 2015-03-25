#include <iostream>
struct aggregate{
    aggregate() = delete;
    int i,j,k;
//private:
//    int l;
};
int main(){
   aggregate a{1,2,3}; // aggregate initialization works, if this is an aggregate :)
   std::cout << a.i;
}

