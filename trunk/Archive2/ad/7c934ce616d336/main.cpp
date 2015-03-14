#include <functional>
#include <tuple>
#include <utility>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <iostream>

using namespace std;

// specialize as needed.
template<class T>
T do_unpack(uint8_t * data){
    T val;
    memcpy(&val, data, sizeof(T));
    return val;
}

template<size_t I, class T, class... Ts>
struct get_offset_temp {
    static constexpr size_t value = get_offset_temp<I-1, Ts...>::value + sizeof(T);
};

template<class T, class...Ts>
struct get_offset_temp<0, T, Ts...>{
    static constexpr size_t value = 0;
};

// compute the offset of the I-th element
template<size_t I, class... Ts>
//constexpr 
size_t get_offset(){
    // assert I < sizeof...(Ts) if needed.
    std::initializer_list<size_t> sizes = { sizeof(Ts)... };
    size_t ret = 0;
    for(auto p = sizes.begin(); p != sizes.begin() + I; ++p) 
        ret += *p;
    return ret;
}


template<size_t I, class... Ts>
std::tuple_element_t<I, std::tuple<Ts...>> unpack_arg(uint8_t *data){
     using T = std::tuple_element_t<I, std::tuple<Ts...>>;
     return do_unpack<T>(data + get_offset_temp<I, Ts...>::value);
}

template<class... Ts, size_t... Is>
void unpack(const std::function<void(Ts...)> &f, uint8_t *dataOffset, std::index_sequence<Is...>){
    f(unpack_arg<Is, Ts...>(dataOffset)...);
}

template<class... Ts>
void unpack(std::function<void(Ts...)> f, uint8_t *dataOffset){
    return unpack(f, dataOffset, std::index_sequence_for<Ts...>());
}



void foo1(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, uint64_t g, int64_t h, float i, double j)
{
    cout << +a << "; " << +b << "; " << c << "; " << d << "; " << e << "; " << f << "; " << g << "; " << h << "; " << i << "; " << j << endl;
}

void foo2(uint8_t a, int8_t b, uint16_t c, int16_t d, uint32_t e, int32_t f, int64_t g, uint64_t h, float i, double j)
{
    cout << +a << "; " << +b << "; " << c << "; " << d << "; " << e << "; " << f << "; " << g << "; " << h << "; " << i << "; " << j << endl;
}

int main()
{
    uint8_t *buff = new uint8_t[512];
    uint8_t *offset = buff;

    uint8_t a = 1;
    int8_t b = 2;
    uint16_t c = 3;
    int16_t d = 4;
    uint32_t e = 5;
    int32_t f = 6;
    uint64_t g = 7;
    int64_t h = 8;
    float i = 9.123456789;
    double j = 10.123456789;

    memcpy(offset, &a, sizeof(a));
    offset += sizeof(a);
    memcpy(offset, &b, sizeof(b));
    offset += sizeof(b);
    memcpy(offset, &c, sizeof(c));
    offset += sizeof(c);
    memcpy(offset, &d, sizeof(d));
    offset += sizeof(d);
    memcpy(offset, &e, sizeof(e));
    offset += sizeof(e);
    memcpy(offset, &f, sizeof(f));
    offset += sizeof(f);
    memcpy(offset, &g, sizeof(g));
    offset += sizeof(g);
    memcpy(offset, &h, sizeof(h));
    offset += sizeof(h);
    memcpy(offset, &i, sizeof(i));
    offset += sizeof(i);
    memcpy(offset, &j, sizeof(j));

    std::function<void (uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float, double)> ffoo1 = foo1;
   unpack(ffoo1, buff);
   
#ifdef SECOND
    // uint64_t and in64_t are switched
    std::function<void (uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, int64_t, uint64_t, float, double)> ffoo2 = foo2;
    unpack(ffoo2, buff);
#endif
    return 0;
}