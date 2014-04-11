#define REPEAT1(m, x) REPEAT1_##x(m)

#define REPEAT1_1(m) m(1)
#define REPEAT1_2(m) REPEAT1_1(m) m(2)
#define REPEAT1_3(m) REPEAT1_2(m) m(3)

#define REPEAT2(m, x) REPEAT2_##x(m)

#define REPEAT2_1(m) m(1)
#define REPEAT2_2(m) REPEAT2_1(m) m(2)
#define REPEAT2_3(m) REPEAT2_2(m) m(3)

#define MACRO(i) int x##i;
#define LOOP(i) REPEAT2(MACRO, i)

int main() {
//    LOOP(3)
    REPEAT1(LOOP, 3)
}