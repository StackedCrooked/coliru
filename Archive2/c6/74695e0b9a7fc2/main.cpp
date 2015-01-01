#include <iostream>

// change access order for N component vector (not std::vector)
// there will be 255 more like this for different orders in vec4(x, y, z, w)
template <typename T, int N>
struct swizzle {

    T& operator [] (int i){
        return ((T*)this)[N - 1 - i];
    }

    const T& operator [] (int i) const {
        return ((T*)this)[N - 1 - i];
    }
};

// n component vector
template <typename T, int N>
struct vec {

    union {
        struct { T x, y; };
        T buf[N];
        swizzle<T, N> yx;
        // 255 more like this here ...
    };

          T& operator [] (int i)       { return buf[i]; }
    const T& operator [] (int i) const { return buf[i]; }

    vec(){}

    explicit vec(T x, T y): x(x), y(y){}

    vec(const swizzle<T, N> &s): x(s[0]), y(s[1]){}
};

template <typename T, int N>
vec<T, N> operator + (const vec<T, N> &a, const vec<T, N> &b){
    vec<T, N> c;
    for (int i = 0; i < N; i++) c[i] = a[i] + b[i];
    return c;
}

// 3 times the same function as above
template <typename T, int N> vec<T, N> operator + (const     vec<T, N> &a, const swizzle<T, N> &b){ return           a  + vec<T, N>(b); }
template <typename T, int N> vec<T, N> operator + (const swizzle<T, N> &a, const     vec<T, N> &b){ return vec<T, N>(a) +           b ; }
template <typename T, int N> vec<T, N> operator + (const swizzle<T, N> &a, const swizzle<T, N> &b){ return vec<T, N>(a) + vec<T, N>(b); }

typedef vec<double, 2> vec2;

int main(){

    vec2 a = vec2(1.0, 2.0);
    vec2 b = vec2(3.0, 5.0);

    // desired syntax (li
    vec2 c = a    + b;
    vec2 d = a.yx + b;
    vec2 e = a    + b.yx;
    vec2 f = a.yx + b.yx;

    std::cout << c.x << " " << c.y << std::endl;
    std::cout << d.x << " " << d.y << std::endl;
    std::cout << e.x << " " << e.y << std::endl;
    std::cout << f.x << " " << f.y << std::endl;

    return 0;
}