template <class T> struct base_vec2 {
    typedef T scalar_type;
    T a, b;
    base_vec2 (T a, T b) : a(a), b(b) {} // construct for two scalar calues
};
template <class T> struct base_vec3 {
    typedef T scalar_type;
    T a, b, c;
    base_vec3 (T a, T b, T c) : a(a), b(b), c(c) {} // construct for three scalar calues
};
template <class T> struct base_box {
    typedef typename T::scalar_type scalar_type;
    T lower, upper; //<! upper and lower point
    base_box<T> (const T& min, const T& max)
        : lower(min), upper(max)
    { }
};

int main() {
    base_box<base_vec3<float>> box { { 1,2,3 }, { 4,5,6 } };
}
