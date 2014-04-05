#include <boost/preprocessor.hpp>

#define DECLARE_VAR(r, data, type) type BOOST_PP_CAT(instance,type);
#define EXPAND(seq) BOOST_PP_SEQ_FOR_EACH(DECLARE_VAR,,seq)

#define FRUITS (Apple)(Banana)(Plum)

int main() {
    EXPAND(FRUITS)
}