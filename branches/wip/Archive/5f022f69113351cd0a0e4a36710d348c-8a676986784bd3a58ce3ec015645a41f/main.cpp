class A{
public:
    int variable;
    A(): variable(4) {}
};

class B : public A{
public:
  void function(){
    new A;
  }
};

int main() {
    B();
}