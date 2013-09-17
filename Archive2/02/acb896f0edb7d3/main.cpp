#include <cassert>
#include <climits>

int type_id_seq;

template<typename T>
struct type_id
{
    static int const value;
};

template<typename T>
int const type_id<T>::value = (assert(type_id_seq < INT_MAX), ++type_id_seq);



template struct type_id<int>;
