struct X{
  int mem;
  decltype(mem) foo(){ return 0; }
};

int main(){
  X x;
  x.foo();
}