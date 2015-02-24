struct A {
  A() {};
  A(int) {};
};

struct B : A
{
   B() = default;

   using A::A;
   B(int, int){}
};

int main()
{
    B b0{};
    B b1{24};
    B b2{24, 42};
}
