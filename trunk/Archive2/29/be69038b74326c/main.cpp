template<typename Lhs>
struct ComparisonDecomposedToLhs {
    const Lhs &lhs;
    
    ComparisonDecomposedToLhs(const Lhs &lhs_) : lhs(lhs_) {}
};

struct ComparisonDecomposer {
    template<typename Lhs>
    ComparisonDecomposedToLhs<Lhs> operator->*(const Lhs &lhs) {
        return ComparisonDecomposedToLhs<Lhs>(lhs);   
    }
};

template<typename Lhs, typename Rhs>
struct DecomposedComparison {
    const Lhs &lhs;
    const Rhs &rhs;
    
    DecomposedComparison(const Lhs &lhs_, const Rhs &rhs_) : lhs(lhs_), rhs(rhs_) {}
};

template<typename Lhs, typename Rhs>
DecomposedComparison<Lhs, Rhs> operator==(ComparisonDecomposedToLhs<Lhs> decomposed, const Rhs &rhs) {
    return DecomposedComparison<Lhs, Rhs>(decomposed.lhs, rhs);
}

#include <iostream>
#include <string>

template<typename Lhs, typename Rhs>
void require(bool result, DecomposedComparison<Lhs, Rhs> comparison, const std::string &comparisonString) {
    if (!result) {
        std::cout << "TEST FAILED\n\tExpression: " << comparisonString << "\n\tEvaluated expression: " << comparison.lhs << " == " << comparison.rhs << "\n";   
    }
}

#define REQUIRE(expr) require((expr), ComparisonDecomposer()->*expr, #expr)

int add(int x, int y) {
    return x * y;   
}

int main() {
    REQUIRE(add(5, 3) == 2*4);
}