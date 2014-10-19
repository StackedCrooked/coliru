#include <type_traits>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

    template<class T,std::size_t N>
    constexpr std::size_t size( T(&)[N] ) { return N; }
    template<class C>
    constexpr auto size(C&& c)->decltype(c.size()) { return c.size(); }

    template<class Kind>
    struct named_operator {};
    static struct append_tag:named_operator<append_tag> {
      template<class T, class A, class RHS>
      static std::vector<T,A>& plus_assign(std::vector<T,A>&lhs, RHS&& rhs) {
        auto rhs_size = size(rhs);
        lhs.reserve(lhs.size()+rhs_size);
        using std::begin; using std::end;
        if (std::is_lvalue_reference<RHS&&>::value)
          copy_n( begin(rhs), rhs_size, back_inserter(lhs) );
        else
          copy_n( std::make_move_iterator(begin(rhs)), rhs_size, back_inserter(lhs) );
        return lhs;
      }
      template<class LHS, class RHS>
      static LHS plus( LHS lhs, RHS&& rhs ) {
        using std::begin; using std::end; using std::back_inserter;
        if (std::is_lvalue_reference<RHS&&>::value)
          copy_n( begin(rhs), size(rhs), back_inserter(lhs) );
        else
          copy_n( std::make_move_iterator(begin(rhs)), size(rhs), back_inserter(lhs) );
        return std::move(lhs);
      }
    } append;
    template<class OP, class LHS> struct plus_ {
      LHS lhs;
      template<class RHS>
      decltype(auto) operator=(RHS&&rhs)&&{
        return OP::plus_assign(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
      }
      template<class RHS>
      decltype(auto) operator+(RHS&&rhs)&&{
        return OP::plus(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
      }
    };
    template<class Tag, class LHS>
    plus_<Tag,LHS> operator+( LHS&& lhs, named_operator<Tag> ) {
      return {std::forward<LHS>(lhs)};
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