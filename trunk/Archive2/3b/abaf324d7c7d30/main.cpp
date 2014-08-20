#include <iostream>

//named parameters
template<class L, class F>
class boundleft {
    L lhs;
    F func;
public:
    boundleft(L lhs,F func):lhs(lhs),func(func){}
    template<class R>auto operator>(R&& rhs)->decltype(func(lhs,rhs)){return func(std::forward<L>(lhs),std::forward<R>(rhs));}
};
template<class L, class F>
boundleft<L,F> operator<(L&& l, F&& f) {return {std::forward<L>(l),std::forward<F>(f)};}
//end named parameters

class mathvector {
public:
    mathvector cross(const mathvector& rhs) const {return {};}
    mathvector dot(const mathvector& rhs) const {return {};}
};
auto cross = [](const mathvector& lhs, const mathvector& rhs) -> mathvector {return lhs.cross(rhs);};
auto dot = [](const mathvector& lhs, const mathvector& rhs) -> mathvector {return lhs.dot(rhs);};

int main() {
    mathvector left;
    mathvector right;
    mathvector result = left <cross> right;
    mathvector result2 = left <dot> right;
    return 0;
}