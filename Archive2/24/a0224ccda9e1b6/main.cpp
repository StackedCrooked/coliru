#include <iostream> 
using namespace std; 

class K { 
public: 
    virtual void add_st(K*) {
      cout << "add_st (K*) from K\n";
    } 
};

class L: public K { 
public: 
    virtual void add_st(L*) {
      cout << "add_st (L*) from L\n";
    } 
}; 

int main() { 
    L ob, ob2;
    K  k, *pl = &ob; 
    pl->add_st(&ob2); 
    return 0; 
} 