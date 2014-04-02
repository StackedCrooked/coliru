template <class O1, class O2>
struct Outer {
  template <class I1, class I2>
  struct Inner { double d; };
};

template <class O1, class O2>
template <class I2>
struct Outer<O1, O2>::Inner<int, I2> { int i; };

template <>
template <class I2>
struct Outer<double, int>::Inner<char, I2> { char c; };



int main() {
  Outer<double, double>::Inner<double, double> OddIdd;
  OddIdd.d = 4.2;
  
  Outer<double, double>::Inner<int, double> OddIid;
  OddIid.i = 5;
  
  Outer<double, int>::Inner<char, double> OdiIcd;
  OdiIcd.c = 'z';
  
    
}  
    
