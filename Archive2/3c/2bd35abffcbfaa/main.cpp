template <class TYPE>
struct S {
  typedef TYPE type;
};

struct A {
  private:
    struct B {
        int c;
    };

  public:
    typedef S<B> SB;
};

int main()
{
    A::SB::type b;
    b.c = 4;
}