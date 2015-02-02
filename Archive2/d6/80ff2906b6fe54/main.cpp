#include <string>
#include <vector>
#include <iostream>
#include <utility>

    namespace named_operator {
      template<class D>struct make_operator{};
    
      template<class T, char, class O> struct half_apply { T&& lhs; };
    
      template<class Lhs, class Op>
      half_apply<Lhs, '*', Op> operator*( Lhs&& lhs, make_operator<Op> ) {
          return {std::forward<Lhs>(lhs)};
      }
    
      template<class Lhs, class Op, class Rhs>
      auto operator*( half_apply<Lhs, '*', Op>&& lhs, Rhs&& rhs )
      -> decltype( invoke( std::forward<Lhs>(lhs.lhs), Op{}, std::forward<Rhs>(rhs) ) )
      {
          return invoke( std::forward<Lhs>(lhs.lhs), Op{}, std::forward<Rhs>(rhs) );
      }
    }
    
namespace vector_ops {
    struct append_tag {};
    static named_operator::make_operator<append_tag> append;

    template<class T, class A1, class A2>
    std::vector<T,A1> invoke( std::vector<T,A1> lhs, append_tag, std::vector<T,A2> const& rhs ) {
        lhs.insert(lhs.end(), rhs.begin(), rhs.end());
        return std::move(lhs); // RVO blocked
    }
}

using vector_ops::append;

int main()
{
    std::vector<std::string> hello = {"hello", " "};
    std::vector<std::string> world = {"world", "!", "\n"};
    for(auto&& s : hello *append* world) {
        std::cout << s;
    }
}
