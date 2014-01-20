struct Foo
{
   typedef decltype(*this) self;

   static void bar()
   {
      self* ptr = nullptr;
   }
};