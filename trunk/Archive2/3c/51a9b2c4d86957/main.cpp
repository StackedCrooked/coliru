#include <type_traits>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>


    // mini named operator library.  Only supports + for now:
    template<class Kind>
    struct named_operator {};
    template<class OP, class LHS> struct plus_ {
      LHS lhs;
      template<class RHS>
      decltype(auto) operator=(RHS&&rhs)&&{
        return plus_assign(std::forward<LHS>(lhs), OP{}, std::forward<RHS>(rhs));
      }
      template<class RHS>
      decltype(auto) operator+(RHS&&rhs)&&{
        return plus(std::forward<LHS>(lhs), OP{}, std::forward<RHS>(rhs));
      }
    };
    template<class Tag, class LHS>
    plus_<Tag,LHS> operator+( LHS&& lhs, named_operator<Tag> ) {
      return {std::forward<LHS>(lhs)};
    }
    
    // creating a named operator:
    static struct append_tag:named_operator<append_tag> {} append;

    // helper function, finds size of containers and arrays:
    template<class T,std::size_t N>
    constexpr std::size_t size( T(&)[N] ) { return N; }
    template<class C>
    constexpr auto size(C&& c)->decltype(c.size()) { return c.size(); }

    // implement the vector +append= range:
    template<class T, class A, class RHS>
    std::vector<T,A>& plus_assign(std::vector<T,A>&lhs, append_tag, RHS&& rhs) {
      auto rhs_size = size(rhs);
      lhs.reserve(lhs.size()+rhs_size);
      using std::begin; using std::end;
      copy_n( begin(rhs), rhs_size, back_inserter(lhs) );
      return lhs;
    }
    // implement container +append+ range:
    template<class LHS, class RHS>
    LHS plus( LHS lhs, append_tag, RHS&& rhs ) {
      using std::begin; using std::end; using std::back_inserter;
      copy_n( begin(rhs), size(rhs), back_inserter(lhs) );
      return std::move(lhs);
    }
    
    
int main() {
    std::vector<int> a = {1,2,3};
    a +append= a;
    for(int x:a)
        std::cout << x << ",";
    std::cout <<"\n";
    std::vector<int> b = {4,5,6};
    for(int x: a+append+b)
        std::cout << x << ",";        
}