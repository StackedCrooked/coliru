#include <iostream>
#include <memory>

class AbstractBase {
public:
    virtual ~AbstractBase() {}
    virtual void doSomething() = 0;
};

class Implementation : public virtual AbstractBase {
public:
    ~Implementation() override {
        std::cout << "Bye!\n";
    }
    virtual void doSomething()override{
        std::cout<<"hello!"<<std::endl;
    }
};

struct placement_delete {
  template <typename T>
  void operator () (T* ptr) const {
    ptr->~T();
  }
};

int main(){
    std::aligned_storage<sizeof(Implementation)>::type space;
    
    std::unique_ptr<AbstractBase,placement_delete> base{new (&space) Implementation};
    
    //then how can I call destructor of Implementation from
    //base? (I know I can't delete base, I just want to call its destructor)
    return 0;
}
