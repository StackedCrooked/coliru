template <typename T>
class A
{
public:
  template <typename C>
  class B
  {
  public:
    C* cptr;
  };

  typedef typename A<T>::B<T> Ttype;
};

int main(int argc,char** argv)
{
  A<int>::Ttype d;
  d.cptr = 0;
}