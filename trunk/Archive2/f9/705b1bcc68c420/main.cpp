#include <iostream>

class singleton{
  private:
  static singleton * instance;
  ~singleton(){};
  public:
  static singleton * getInstance(){
      if (instance == NULL){
          instance = new singleton;
      }
      return instance;
  }
  void fun(){
      std::cout<<"Hello\n";
  };
};
singleton * singleton::instance = NULL;
int main()
{
    singleton s;
    singleton *p = singleton::getInstance();
    p->fun();
    std::cout<<p<<"\n";
    singleton *q = singleton::getInstance();
    q->fun();
    std::cout<<q<<"\n";
}