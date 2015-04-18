#include <iostream>
#include <string>
#include <cmath>


template <typename Tx = float>
struct SomethingGeneric {
    
    SomethingGeneric(Tx x) : _x(x) {};
    
    private:
        Tx _x;
};


template <typename Tx = float>
static SomethingGeneric<Tx> Something(Tx&& x) {
	return { std::forward<Tx>(x) };
};


// Just testing out passing in some stuff
SomethingGeneric<> foobar(float x) {
    return Something(x);
};


// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
  
   
	return 0;
}



