#include <iostream>

class foobar {
  private:
  int x_;
  public:
  foobar() : x_(0) {};
  void show(foobar& v) {
    std::cout << v.x_ << std::endl;
  };
  void manip(foobar& f, int v) {
    f.x_ = v;
  };
};


int main(void)
{
  foobar a;
  foobar b;
  
  b.show(a);
  b.manip(a, 1);
  b.show(a);
  
  return 0;
}