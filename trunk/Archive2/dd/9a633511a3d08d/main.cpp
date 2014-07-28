#include <iostream>

struct Base { 
    virtual void print() {}
};

int main(int, char**) {
   Base storage[1];
   storage[0].print();

   std::cout <<"Succeed";
   return 0;
}