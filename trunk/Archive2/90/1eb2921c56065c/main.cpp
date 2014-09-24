#include <iostream>
#include <utility>

class ResourceType
{
public:
   void acquire() const{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
   void release() const{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
   void acquire() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
   void release() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

template< class T >
class RAIIClass;
template <typename T>
RAIIClass<T> make_guard(T&&);

template< class T >
class RAIIClass
{
public:
   ~RAIIClass() { std::cout << __PRETTY_FUNCTION__ << '\n'; t.release(); }

private:
   friend RAIIClass make_guard<>(T&&);
   RAIIClass(T&& in_t) : t(std::forward<T>(in_t)) { t.acquire(); }

   T t;
};

template <typename T>
RAIIClass<T> make_guard(T&& t)  {
   return {std::forward<T>(t)};
}

ResourceType foo() { return {}; }

int main()
{
   ResourceType x1;
   const ResourceType & x2(x1);

   {
      auto x = make_guard(x1); //Allowable
   }
   {
      auto x = make_guard(x2); //Allowable
   }
   {
      auto x = make_guard(foo()); //Allowable too.
   }
}
