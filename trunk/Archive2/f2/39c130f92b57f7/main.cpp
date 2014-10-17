template <class T>
class A {
    int i;
  public:
    template <class U>
    void copy_i_from( const A<U> & a ){
        i = a.i;
    }
    
    template<typename U>
    template<typename UU>
    friend void A<U>::copy_i_from(const A<UU>&);
};

int main(void) {
    A<int> ai;
    A<double> ad;
    ai.copy_i_from(ad);
    return 0;
}