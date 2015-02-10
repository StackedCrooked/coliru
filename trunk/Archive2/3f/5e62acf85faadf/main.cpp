#include <iostream>
#include <type_traits>
#include <functional>

struct book {};
struct sender { void with_param( int n ) { std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called with " << n << "\n"; } };
struct sender_test { void book_complete() { std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called \n"; } };

#define OPTIONAL_MEM_CALL_DEF(Func) \
  template<class T> struct has_member_##Func { \
    template<class C> static char test( decltype(&C::Func) ) ; \
    template<class C> static int test( ... ); \
    enum { value = ( sizeof( test<T>( 0 ) ) == sizeof( char ) ) }; }; \
  template<class C, typename... Args, typename std::enable_if<has_member_##Func<C>::value, int>::type = 0> \
  void optional_mem_call_##Func( C& callback, Args&&... args ) { callback.Func( std::forward<Args>( args )... ); } \
  template<class C, typename... Args, typename std::enable_if<!has_member_##Func<C>::value, int>::type = 0> \
  void optional_mem_call_##Func( C& callback, Args&&... ) { std::cout << " callback ignored: " << __PRETTY_FUNCTION__ << " called \n"; }

OPTIONAL_MEM_CALL_DEF(book_complete)
OPTIONAL_MEM_CALL_DEF(with_param)

template<class callback_t>
struct interface
{
  callback_t m_callback;
  void make_book( book* book )
  {
    if ( nullptr == book )
      optional_mem_call_book_complete(m_callback);
  }
  void with_param()
  {
    optional_mem_call_with_param( m_callback, 3 );
  }
};

void run_test()
{
  interface<sender_test> test;
  test.make_book(nullptr);
  test.with_param();
}
void run_real()
{
  interface<sender> real;
  real.make_book(nullptr);
  real.with_param();
}


int main()
{
    run_test();
    run_real();
}
