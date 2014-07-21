struct B { 
  int b; 
  B(int i = 0) : b(i) {};  // constructor
};

struct D : B  {
    using B::B;
  int d;
};

int main () {
  D obj = {1};  // <-- error
   D obj2 {1};  // <-- more errors!
}
