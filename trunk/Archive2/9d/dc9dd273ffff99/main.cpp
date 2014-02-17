class B {};
struct A 
{
  A(B const&) {}
private:
  A(A const&);
};


int main()
{
    B b;
    A a1 = {b};
//    A a2 = b;
}
