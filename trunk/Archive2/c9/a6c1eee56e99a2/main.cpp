#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <type_traits>

/**  Moves visitor over all entries */
namespace TupleVisit{

        template<std::size_t Idx = 0,
                 typename Visitor,
                 typename... T,
                 typename std::enable_if< Idx < sizeof...(T) , void *>::type = nullptr
                 >
        static
        void visit(Visitor && v, std::tuple<T...>  & t){
            v( std::get<Idx>(t) );
            TupleVisit::visit<Idx+1, Visitor, T... >(std::forward<Visitor>(v),t);
        }
        
        
        template<std::size_t Idx = 0,
                 typename Visitor,
                 typename... T,
                 typename std::enable_if< Idx == sizeof...(T) , void *>::type = nullptr
                  >
        static void
        visit(Visitor && v, std::tuple<T...> & t){}
}


struct vis{
  
  template<typename T>
  void operator()(T & t){
    std::cout << t << std::endl;   
  }
  
};

int main()
{
    std::tuple<int,int> a{1,2};
    
    TupleVisit::visit(vis{},a);

}
