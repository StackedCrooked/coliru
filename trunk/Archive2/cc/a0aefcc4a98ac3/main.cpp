#include <utility>
#include <iostream>

template< typename Signature >
class Delegate;

template< typename Ret, typename Param >
class Delegate< Ret(Param) >
{
public:
   
   Ret operator()(Param&& p_param)
   {
      return m_ifunc(m_obj, std::forward< Param >(p_param));
   }
   
   template< typename ObjType, Ret(ObjType::*Method)(Param) >
   friend Delegate< Ret(Param) > createDelegate(ObjType * const p_obj)
   {
      Delegate< Ret(Param) > del;
      del.m_obj = p_obj;
      del.m_ifunc = &ifunction< ObjType, Method >;
      return del;
   }
   
private:
   
   void * m_obj = nullptr;
   Ret (*m_ifunc)(void*, Param&&) = nullptr;
   
   template< typename ObjType, Ret(ObjType::*Method)(Param) >
   static Ret ifunction(void * const p_obj, Param&& p_param)
   {
      ObjType * const obj = (ObjType * const) p_obj;
      return (obj->*Method)(std::forward< Param >(p_param));
   }
};

struct Test
{
   void test(int x)
   {
      std::cout << x << std::endl;
   }
   
};

int main()
{
   Test t;
   
   Delegate< void(int) > d = createDelegate< Test, &Test::test >(&t);
   
   d(5);
}