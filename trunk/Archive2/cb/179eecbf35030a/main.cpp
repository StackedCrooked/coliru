#include <iostream>
struct aggregate{
    aggregate() = delete;
    int i,j,k;
};
int main(){
   aggregate a{1,2,3};
   std::cout << a.i;
}

