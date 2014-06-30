#include <memory>

template <class T>
struct raw_ptr_type;

template <class T>
struct raw_ptr_type<T*> {
  typedef T* type;
};

template <class U>
struct raw_ptr_type<std::shared_ptr<U>> {
  typedef typename std::shared_ptr<U>::element_type* type;
};

//===================================


#include <iostream>

struct Base {
  virtual void foo() { std::cout << "UPO\n"; }    
};

struct Derived : Base {
  virtual void foo() override { std::cout << "BSomething\n"; }
}; 

//===================================

template <class Cont>
void bar(Cont& cont)
{
  Base* pcoPO = new Derived();
  
  typedef typename Cont::value_type value_type;
  typedef typename raw_ptr_type<value_type>::type raw_ptr;
  
  raw_ptr rawPO = static_cast<raw_ptr>(pcoPO); //downcast
  cont.push_back( value_type(rawPO) );
}

//===================================


#include <vector>

int main()
{
  std::vector<Derived*> someVec;
  bar(someVec);
  
  for (auto const& p : someVec) {
    p->foo();
  }
  
  std::vector<std::shared_ptr<Derived>> someSharedVec;
  bar(someSharedVec);
    
  for (auto const& p : someSharedVec) {
    p->foo();
  }
}
