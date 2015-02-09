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
  template<class C, typename std::enable_if<has_member_##Func<C>::value, int>::type = 0> \
  void optional_mem_call_##Func( C& callback ) { callback.Func(); } \
  template<class C, typename std::enable_if<!has_member_##Func<C>::value, int>::type = 0> \
  void optional_mem_call_##Func( C& callback ) { std::cout << " callback ignored: " << __PRETTY_FUNCTION__ << " called \n"; }

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
