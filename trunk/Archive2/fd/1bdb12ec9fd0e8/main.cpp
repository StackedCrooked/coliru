struct Foo
{
   Foo(const Foo &)=delete;
   Foo(Foo &&)=delete;
   Foo &operator=(const Foo&)=delete;
   Foo &operator=(Foo &&)=delete;
   
   Foo(int){}
};

Foo create()
{
   //return Foo{0}; // ERROR: needs Foo(self &&)
   return {0};
}

int main()
{
   auto &&t=create();
   (void)t;
}
