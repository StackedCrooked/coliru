#include <iostream>
#include <string>
#include <vector>

template<int size>
struct A{    
    int id = 5;
    void loop(){        
        for (int i=0;i<size;i++){
            std::cout << "A";
        }
    }
};

template<int i = 15>
using ty = A<i>;


#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,##__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)
#define VARARG_IMPL_(base, count, ...) base##count(__VA_ARGS__)
#define VARARG_IMPL(base, count, ...) VARARG_IMPL_(base, count, __VA_ARGS__)
#define VARARG(base, ...) VARARG_IMPL(base, VA_NARGS(__VA_ARGS__), __VA_ARGS__)





#define FIELD_STR3(a, b, c) A<c> a;
#define FIELD_STR4(a, b, c, d) A<c+d> a;
#define FIELD_LIST LIST(FIELD_STR)


#define FIELD_STR(...) VARARG(FIELD_STR, __VA_ARGS__)

#define LIST(x) \
    x(chunksize1, int, 100) \
    x(construct1, int, 1,2)
FIELD_LIST    
//#undef LIST


#define LIST(x) \
    x(chunksize, int, 100) \
    x(construct, int, 12)

FIELD_LIST



int main()
{
/*    ty<> a;
    a.loop();*/
    construct1.loop();
}
