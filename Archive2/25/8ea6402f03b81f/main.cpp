template<class D, class B>
class is_derived
{
private:
  class Yes { char a[1]; };
  class No { char a[10]; };

  static Yes Test( B* );
  static No Test( ... );

public:
  constexpr static bool value = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes);
};

class X {};

template <typename T>
class Test
{
    static_assert(is_derived<T,X>::value, "Not derived from X");
};

class A : public X {};
class B  {};

int main()
{
    Test<A> a; // OK
    //Test<B> b; // NOT OK
}
