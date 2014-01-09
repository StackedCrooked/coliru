#include <boost/concept_check.hpp>

template <typename X>
class  ConceptsBase {};

int main() {
    auto l = [](){};

    BOOST_CONCEPT_ASSERT((ConceptsBase<decltype(l)>));

    return 0;
}   