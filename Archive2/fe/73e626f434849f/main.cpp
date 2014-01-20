#include <iostream>
#include <functional>

using namespace std;

class helper_ { public: int operator()( int, char ) { return 42; } };

template<typename _Ty>
_Ty func_( const _Ty &);

template<typename _Ty, typename _Ret = decltype( &_Ty::operator() )>
_Ret func_2( const _Ty &);



template<typename... _Types>
struct type_holder{};

template<typename... _Types>
struct decl_fun_type;


template<typename _Ret, typename... _Args>
struct decl_fun_type<_Ret( _Args... )>
{
  using ret_type = _Ret;
};


template<class _Cl, typename _Ret, typename... _Args>
struct decl_fun_type<_Ret( _Cl::*)( _Args... )>
{
  using ret_type = _Ret;
  using args_type = type_holder<_Args...>;
};

int main()
{
  auto a = [] ( int, char, char, size_t ) mutable -> char {return 42;};
  auto b = helper_ {};

  using a_t = decltype( a );
  using b_t = decltype( b );

  cout << typeid( decltype(func_(a)) ).name() << endl;
  cout << typeid( decltype(func_(b)) ).name() << endl;
  cout << endl;

  cout << typeid( decltype( func_2(a) )).name() << endl;
  cout << typeid( decltype( func_2(b) )).name() << endl;
  cout << endl;


  cout << typeid( decl_fun_type<decltype( &a_t::operator() )>::ret_type ).name() << endl;
  cout << typeid( decl_fun_type<decltype( &b_t::operator() )>::ret_type ).name() << endl;
  cout << endl;


  cout << typeid( decl_fun_type<decltype( &a_t::operator() )>::args_type ).name() << endl;
  cout << typeid( decl_fun_type<decltype( &b_t::operator() )>::args_type ).name() << endl;
  cout << endl;

  getchar();
}