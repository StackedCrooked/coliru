#include <iostream>
#include <stdexcept>

using namespace std;

class myobj {
public:
  myobj(int val) : qty_(val) {}
  int qty() const { return qty_;}
private:
  int qty_;
};

template<class T>
int get_quantity(const T& o) {
  throw runtime_error("get_quantity<T> not implemented");
}

template<>
int get_quantity(const myobj& o) {
  return o.qty();
}

struct QtyAsc {
  template<class T, class QEx >
  bool operator()(const T& o1, const T& o2, QEx extr) const {
    return extr(o1) < extr(o2);
  }
  template<class T>
  bool operator()(const T& o1, const T& o2) const {
    return operator()(o1, o2, &get_quantity<T>);
  }
};

int main() {
  myobj t1(10),t2(20);

  QtyAsc asc;
  if(asc(t1,t2))
    cout << "Yes" << endl;
}
