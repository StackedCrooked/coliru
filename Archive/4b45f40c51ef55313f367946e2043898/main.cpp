

template<typename T>
class Proxy
{
    T * t;
};


#define EXCENTIS_PTR_DEBUG 1

template<typename T, int = EXCENTIS_PTR_DEBUG>
struct PtrType;

template<typename T>
struct PtrType<0> { typedef  T * type; };

template<typename T>
struct PtrType<1> { typedef CheckedPtr<T> type; };


struct Item;
typedef typename PtrType<Item>::type ItemPtr;

ItemPtr item;






