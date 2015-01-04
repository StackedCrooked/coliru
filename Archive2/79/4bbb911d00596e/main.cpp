#include <iostream>
#pragma GCC diagnostic ignored "-Wunused-variable"


using namespace std;


struct s {};

//void f0 (      s& x) { cout << "#1"; }  // #1
void f0 (const s& x) { cout << "#2";  }  // #2
//void f0 (      s&& x) { cout << "#3";  } // #3
//void f0 (const s&& x) { cout << "#4";  } // #4

const s g () { return s(); }

int main()
{
    s x;
    const s cx;

//    f0 (s ()); // rvalue        #3, #4, #2
    f0 (g ()); // const rvalue  #4, #2
//    f0 (x);    // lvalue        #1, #2
//    f0 (cx);   // const lvalue  #2

    return 0;
}
