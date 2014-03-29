#include <iostream>
#include <functional>
#include <typeinfo>

/*
 * 1. In block, every generated lambda has a unique type.
 * 2. switch cases , thus goto, has it's own block.
 */
using namespace std;

template<typename T>
void TestBloat(T t)
{
   t();
   cout << typeid(t).name() << endl;
}

void Test()
{
   TestBloat([]{});
   TestBloat([]{});
}

int main()
{
   cout << "for loop without branch" << endl;
   for(int i = 0 ; i <= 4; i++)
   {
      TestBloat([=]{cout << i << endl;});
      TestBloat([=]{cout << i << endl;});
   }

   int j;

   cout << endl;
   cout << "for loop with branches" << endl;
   for(int i = 0 ; i <= 4; i++)
   {
    i%2 ? j = i + 1 : j = 0;

    if (i < j)
      TestBloat([=]{cout << i << endl;});
    else
      TestBloat([=]{cout << i << endl;});

    switch (i)
    {
      case 1:
         TestBloat([=]{cout << i << endl;});
      case 2:
         TestBloat([=]{cout << i << endl;});
      case 3:
         TestBloat([=]{cout << i << endl;});
      case 4:
         TestBloat([=]{cout << i << endl;});
    }
   }

   cout << endl;
   cout << "for loop with function calls" << endl;
   for(int i = 0 ; i <= 4; i++)
   {
      Test();
   }
}
