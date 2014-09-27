struct B{
  B():x(42){}
  int doSomeStuff() const{return x;}
  int x;
};

struct A{
  
  B b;//not required for this example, just to illustrate
      //how this situation isn't totally useless
};

int main(){
  const A a;
}