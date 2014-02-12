#include <iostream>
using std::cout;
using std::cin;
using std::endl;

struct Blob {
  Blob() { cout << "C" << endl; }
  Blob(const Blob&) { cout << "c" << endl; }
  Blob(Blob&&) { cout << "m" << endl; }
  Blob& operator =(const Blob&) { cout << "=" << endl; return *this; }
  Blob& operator =(Blob&&) { cout << "=m" << endl; return *this; }
  ~Blob() { cout << "~" << endl; }

  int i;
};

int main() {
  try {
     cout << "Throw directly: " << endl;
     throw Blob();
  } catch(const Blob& e) { cout << "caught: " << &e << endl; }
  try {
     cout << "Throw with object about to die anyhow" << endl;
     Blob b;
     throw b;
  } catch(const Blob& e) { cout << "caught: " << &e << endl;  }
  {
    cout << "Throw with object not about to die anyhow (enter non-zero integer)" << endl;
    Blob b;
    int tmp;
    cin >> tmp; //Just trying to keep optimizers from removing dead code
    try {
      if(tmp) throw b;
      cout << "Test is worthless if you enter '0' silly" << endl;
    } catch(const Blob& e) { cout << "caught: " << &e << endl;  }
    b.i = tmp;
    cout << b.i << endl;
  }
}