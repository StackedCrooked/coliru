#include <iostream>
#include <vector>

template <typename T> class foo
{
  T attribute1;
  std::vector<foo*> attribute2;  

 public:
  foo(const T& data):attribute1(data){}

  // Some methods

  foo* getAttribute2(int pos)const
  {
    if (pos<0 || pos>=attribute2.size()) 
        throw "In foo::getAttribute2, argument out of range";
    return attribute2[pos]; // One can also use "return sons.at(pos)" which handles itself range problems
} 

  void foo2vector(std::vector<T>& v)
  {
    v.push_back(attribute1);
    if (attribute2.size()>0) 
    {
        for(unsigned int i=0; i<attribute2.size();i++) 
            attribute2[i]->foo2vector(v);
    }
  }
};

int main()
{
   foo<int> f(5);
   std::vector<int> v;
   f.foo2vector(v);
   std::cout << "ok" << std::endl;
   return 0;
}
