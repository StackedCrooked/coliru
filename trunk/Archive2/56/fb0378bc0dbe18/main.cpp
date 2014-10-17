template <class T>
class A {
    int i;
  public:
    template <class U>
    void copy_i_from( const A<U> & a ){
        i = a.i;
    }
  template <class F>
  template <class U> friend void A<F>::copy_i_from(const A<U> & a);
};

int main(void) {
    A<int> ai;
    A<double> ad;
    ai.copy_i_from(ad);
    return 0;
}