#include <iostream>
#include <memory>

class HiddenA{
public:
  explicit HiddenA(int i) : _i{i} {}
  
  void machin() const{ std::cout<<"machin "<<_i<<std::endl; }
  void truc(int a){ _i += a; }
  
private:
  int _i;
};

class HandlerA{
public:
  HandlerA(int a) : _ptr{ new HiddenA(a) }{}
  HiddenA* const operator-> () const{ return _ptr.get(); }

private:
  std::unique_ptr<HiddenA> _ptr;
};

int main()
{
    HandlerA a(40);
    a->truc(2);
    a->machin();
}
