#include <iostream>
#include <type_traits>
#include <functional>

struct book {};
struct value {};
struct sender {
    void with_param( int n ) { std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called with " << n << "\n"; }
    void partial( book* b ) {  std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called with book*" << "\n"; }
};
struct sender_test {
    void book_complete() { std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called \n"; }
    void partial( value* v  ) {  std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called with value*" << "\n"; }
    void partial( book* b, value* v  ) {  std::cout << " callback succeeded: " <<  __PRETTY_FUNCTION__ << " called with book* and value*" << "\n"; }
};

#define OPTIONAL_MEM_CALL_DEF(Func) \
  template<class T> struct has_member_##Func { \
    template<class C> static char test( decltype(&C::Func) ) ; \
    template<class C> static int test( ... ); \
    enum { value = ( sizeof( test<T>( 0 ) ) == sizeof( char ) ) }; }; \
  template<class C, typename... Args, typename std::enable_if<has_member_##Func<C>::value, int>::type = 0> \
  void optional_mem_call_##Func( C& callback, Args&&... args ) { callback.Func( std::forward<Args>( args )... ); } \
  template<class C, typename... Args, typename std::enable_if<!has_member_##Func<C>::value, int>::type = 0> \
  void optional_mem_call_##Func( C& callback, Args&&... ) { std::cout << " callback ignored: " << __PRETTY_FUNCTION__ << " called \n"; }

#define OPTIONAL_MEM_CALL_TYPE(Name,Func,...) \
  template<class T> struct has_type_##Name { template<class U, U> class check { }; \
    template<class C> static char test( check<void (C::*)( __VA_ARGS__ ), &C::Func>* ); \
    template<class C> static int test( ... ); \
    enum { value = ( sizeof( test<T>( 0 ) ) == sizeof( char ) ) }; }; \
  template<class C, typename... Args, typename std::enable_if<has_type_##Name<C>::value, int>::type = 0> \
  void optional_mem_call_##Name( C& callback, Args&&... args ) { callback.Func( std::forward<Args>( args )... ); } \
  template<class C, typename... Args, typename std::enable_if<!has_type_##Name<C>::value, int>::type = 0> \
  void optional_mem_call_##Name( C& callback, Args&&... ) { std::cout << " callback ignored: " << __PRETTY_FUNCTION__ << " called \n"; }

OPTIONAL_MEM_CALL_DEF(book_complete)
OPTIONAL_MEM_CALL_DEF(with_param)
OPTIONAL_MEM_CALL_TYPE(partial_book,partial,book*)
OPTIONAL_MEM_CALL_TYPE(partial_value,partial,value*)

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
  void partial( book& c )
  {
    optional_mem_call_partial_book( m_callback, &c );
  }
  void partial( value& c )
  {
    optional_mem_call_partial_value( m_callback, &c );
  }
};

void run_test()
{
  interface<sender_test> test;
  book b;
  value v;
  test.make_book(nullptr);
  test.with_param();
  test.partial( b );
  test.partial( v );
}
void run_real()
{
  interface<sender> real;
  book b;
  value v;
  real.make_book(nullptr);
  real.with_param();
  real.partial( b );
  real.partial( v );
}


int main()
{
    std::cout << std::boolalpha;
    std::cout << "Is function sender_test: " << has_type_partial_value<sender_test>::value <<std::endl;
    std::cout << "Is function sender: " << has_type_partial_value<sender>::value <<std::endl;
    run_test();
    run_real();
}
