#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/type_index.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <tuple>
#include <utility>
using namespace std;

template <typename FuncType>
using Arity = boost::function_types::function_arity<FuncType>;

template <typename FuncType>
using ResultType = typename boost::function_types::result_type<FuncType>::type;

template <typename FuncType, size_t ArgIndex>
using ArgType = typename boost::mpl::at_c<boost::function_types::parameter_types<FuncType>, ArgIndex>::type;

void func(int, char const&, double) {}

template <typename Func, typename IndexSeq>                                                                                                                                                         
struct ArgPrintHelper;

template <typename Func, size_t... Inds>
struct ArgPrintHelper<Func, integer_sequence<size_t, Inds...> >
{
  static void doit()
  {
    string typeNames[] = {boost::typeindex::type_id_with_cvr<ResultType<Func>>().pretty_name(),
                          boost::typeindex::type_id_with_cvr<ArgType<Func, Inds>>().pretty_name()...};
    for (auto const& name : typeNames)
      cout << name << " ";
    cout << endl;
  }
};

template <typename Func>                                                                                                                                                                            
void ArgPrinter(Func f)                                                                                                                                                                             
{                                                                                                                                                                                                   
  ArgPrintHelper<Func, make_index_sequence<Arity<Func>::value> >::doit();                                                                                                                           
}

int main()                                                                                                                                                                                          
{                                                                                                                                                                                                   
  ArgPrinter(func);                                                                                                                                                                                 
  return 0;                                                                                                                                                                                         
}
