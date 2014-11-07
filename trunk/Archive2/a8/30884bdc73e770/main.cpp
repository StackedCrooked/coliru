#define CAT(x,y) CAT_(x,y)
#define CAT_(x,y) x##y

#define IF(cond, t, f) CAT(IF_, cond)(t, f)
#define IF_0(t, f) f
#define IF_1(t, f) t

#define NOTHING(...)

#define REPEAT CAT(REPEAT, MIN_AVAIL_DIM)

#define MIN_AVAIL_DIM IF(DIM_IN_USE(1), 2, 1)

#define DIM_IN_USE(dim) CAT(DIM_IN_USE_, REPEAT##dim(1, NO NOTHING))
#define DIM_IN_USE_NO 0
#define DIM_IN_USE_REPEAT1(x, m) 1

#define REPEAT1(x, m) REPEAT1_##x(m)

#define REPEAT1_1(m) m(1)
#define REPEAT1_2(m) REPEAT1_1(m) m(2)
#define REPEAT1_3(m) REPEAT1_2(m) m(3)

#define REPEAT2(x, m) REPEAT2_##x(m)

#define REPEAT2_1(m) m(1)
#define REPEAT2_2(m) REPEAT2_1(m) m(2)
#define REPEAT2_3(m) REPEAT2_2(m) m(3)

////////////////////////////////////////////////////

#include <iostream>

#define MACRO(i) std::cout << i << ' ';

#define LOOP(i) REPEAT(i, MACRO) std::cout << '\n';

int main() {
    REPEAT(3, LOOP)
}