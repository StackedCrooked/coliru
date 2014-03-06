int main ()
{
   constexpr const int A = 42;
   constexpr const int &B = A;
   
   static_assert(&A == &B, "Bug");
}