template<class>
struct A {
  template<class...> static void func ();
};

template struct A<int>;                    // explicit instantiation of A<int>
extern template void A<int>::func<int> (); // extern instantiation of A<int>::func<int>

int main () {
  A<int>::func<int> ();                    // linker error;
                                           // instantiating A<int> doesn't instantiate func
                                           // meaning that `func` is indeed a template of its
                                           // own, 
  /*
   * [temp.exp.spec]p17 doesn't apply since there's no specialization of
   * A<...>::func<...> that depends on a non-specialized A
   * */
}