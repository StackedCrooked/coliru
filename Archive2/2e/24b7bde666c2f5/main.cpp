template <typename T>
class B
{
public:
  B operator+(const B& rhs)
  {
    return *this;
  }
};

template <typename T>
class A
{
public:
  operator B<T>() const{return B<T>();}
};

template<typename T>
class HolderPlus
{
private:
    const T& lhs;
    const T& rhs;
public:
    HolderPlus( const T& l, const T& r ) : lhs( l ), rhs( r ) {}

    template<typename U>
    operator B<U>() const { return B<U>(lhs) + B<U>(rhs); }
};

template<typename T>
HolderPlus<A<T>> operator+(A<T> const& t, A<T> const& u)
{
  return HolderPlus<A<T>>(t,u);
}

int main()
{
  A<double> a,b;
  B<double> c = a+b;
  (void)c; // suppress warning about unused variable c
  return 0;
}
