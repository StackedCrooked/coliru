#define CAT(a, b) CAT_(a, b)
#define CAT_(a, b) a##b

#define REPEAT1(m) m(1)
#define REPEAT2(m) REPEAT1(m) m(2)
#define REPEAT3(m) REPEAT2(m) m(3)

#define MACRO(i) int x##i;
#define LOOP(i) CAT(REPEAT,i)(MACRO)

int main() {
    LOOP(3)
    REPEAT3(LOOP)
}