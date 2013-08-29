class MyClass{
public:
  double a;
  double rect[4];

  MyClass();
  ~MyClass();
};

MyClass::MyClass() : a(123.0)
{ 
   memset(rect, 0, 4 * sizeof(double)); 
}

MyClass::~MyClass() {}

int main() {
    // I wonder why people insist on this "allocated on stack/heap" crap
    
    new MyClass(); // look me in the eye and tell me the array is allocated on the stack
}