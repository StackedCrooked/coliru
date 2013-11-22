struct Foo { 
  int a; bool b; 
};

class C {
  Foo f;
public:
  C(int i) : f{i, false}
  {}
};

int main() {
  C c{12};   
}
