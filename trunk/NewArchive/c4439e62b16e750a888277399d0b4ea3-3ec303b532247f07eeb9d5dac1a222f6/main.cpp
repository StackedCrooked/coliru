
#define FOO1(arg) struct arg;
#define FOO2(head, ...) FOO1(head) FOO1(__VA_ARGS__)
#define FOO3(head, ...) FOO1(head) FOO2(__VA_ARGS__)
#define FOO4(head, ...) FOO1(head) FOO3(__VA_ARGS__)
#define FOO5(head, ...) FOO1(head) FOO4(__VA_ARGS__)
#define FOO(head, ...) FOO##head(__VA_ARGS__)

FOO(5, A, B, C, D, E)