struct X
{
public:
   template <typename T> static void foo() {}
};

template<typename U>
struct Y
{
public:
   void x();
   
};

template<typename U>
void Y<U>::x()
{
   //U is a dependant type, why not need typename in front of U here?
  U::template X<int>::foo();
}

int main()
{
    Y<int> a;
    a.x();
}