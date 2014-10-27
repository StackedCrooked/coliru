#include <iostream>
#include <vector>

template<class T, class CoordinateSpace>
struct vec2 {
    public:
        T x;
        T y;
};

struct WindowSpace;
struct MapSpace;

template<class T>
struct SpaceConversions {
    template<class CoordinateSpaceA, class CoordinateSpaceB>
    static vec2<T, CoordinateSpaceB> transform(vec2<T, CoordinateSpaceA> in);    
};

template<>
template<class T>
vec2<T, WindowSpace> SpaceConversions<T>::transform(vec2<T, MapSpace> in) {
    return {in.x * 2, in.y * 2};
}

template<>
template<class T>
vec2<T, MapSpace> SpaceConversions<T>::transform(vec2<T, WindowSpace> in) {
    return {in.x / 2, in.y / 2};
}

int main() {
    return 0;
}