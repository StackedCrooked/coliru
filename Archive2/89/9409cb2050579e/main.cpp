class A
{
   virtual void get();
};

class B: public A
{
   void get();
};

class C: public B
{
   void get();
};

int main()
{
   B* i;
   i = new C();
   i.get();
   return (0);
}