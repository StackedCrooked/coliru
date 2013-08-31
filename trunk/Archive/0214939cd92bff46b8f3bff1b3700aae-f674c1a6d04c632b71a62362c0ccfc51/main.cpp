template <typename T, typename U, template <class,class> class Z>
struct B
{

};

template <typename T, typename U>
struct A
{
  B<T,U,A> b;
};


int main()
{
  A <int,float> a;
  return 0;
}
