#include <iostream>
#include <type_traits>
#include <functional>

struct book {};
struct sender { };
struct sender_test { void book_complete() { std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called \n"; } };

#define OPTIONAL_MEM_CALL_DEF(Func) \
  template<class T> struct has_member_##Func { \
    template <class C> static char test( decltype(&C::Func) ) ; \
    template <class C> static int test( ... ); \
    enum { value = ( sizeof( test<T>( 0 ) ) == sizeof( char ) ) }; }; \
  template<bool> struct call_member_##Func; \
  template<> struct call_member_##Func<true> { template<class C> static void run( C& callback ) { callback.Func(); } }; \
  template<> struct call_member_##Func<false> { template<class C> static void run( C& callback) {  std::cout << " callback ignored: " << __PRETTY_FUNCTION__ << " called \n"; } }; \
  template<class C> void optional_mem_call_##Func( C& callback ) { call_member_##Func<has_member_##Func<C>::value>::run( callback ); }

OPTIONAL_MEM_CALL_DEF(book_complete)

template<class callback_t>
struct interface
{
  callback_t m_callback;
  void make_book( book* book )
  {
    if ( nullptr == book )
      optional_mem_call_book_complete(m_callback);
  }
};

void run_test()
{
  interface<sender_test> test;
  test.make_book(nullptr);
}
void run_real()
{
  interface<sender> real;
  real.make_book(nullptr);
}


int main()
{
    run_test();
    run_real();
}
