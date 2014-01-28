#include <boost/preprocessor.hpp>

#define ADD_ATTRIBUTE_HELPER(r, attr, elem) attr elem; 
#define ADD_ATTRIBUTE(attr, seq) BOOST_PP_SEQ_FOR_EACH(ADD_ATTRIBUTE_HELPER, attr, seq)

int main() {
    ADD_ATTRIBUTE(static,
        (int a)
        (int b)
        (int c)
    )
    
    a = b = c = 2;
}
