struct Foo
{
   double temp;

   void bar()
   {
      double temp;       // "hides" the member
      temp = 3.0;        // assigns to the local
      this->temp = 5.0;  // assigns to the member
   }

   void baz()
   {
      temp = 3.0;        // assigns to the member
      this->temp = 5.0;  // assigns to the member
   }
};

int main() {}