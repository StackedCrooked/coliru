#include <iostream>
#include <vector>

template<class T, class CoordinateSpace>
struct vec2 {
    public:
        T x;
        T y;
        bool operator==(const vec2<T, CoordinateSpace>& other) {
            return other.x == x && other.y == y;
        }
};

struct WindowSpace;
struct MapSpace;
struct CameraSpace;

template<class T>
struct SpaceConversions {
    static vec2<T, WindowSpace> transform(vec2<T, MapSpace> in) {
        return {in.x * 2, in.y * 2};
    }
    static vec2<T, WindowSpace> transform(vec2<T, CameraSpace> in) {
        return {in.x * 2, in.y * 2};
    }
    
    static vec2<T, MapSpace> transform(vec2<T, WindowSpace> in) {
        return {in.x / 2, in.y / 2};
    }
    static vec2<T, MapSpace> transform(vec2<T, CameraSpace> in) {
        return {0, 0};
    }
    
    static vec2<T, CameraSpace> transform(vec2<T, WindowSpace> in) {
        return {0, 0};
    }
    static vec2<T, CameraSpace> transform(vec2<T, MapSpace> in) {
        return {0, 0};
    }
};

int main() {
    vec2<float, WindowSpace> in_window = {20.0f, 80.0f};
    std::cout << in_window.x << ", " << in_window.y << "\n";
    vec2<float, MapSpace> in_map = SpaceConversions<float>::transform(in_window);
    std::cout << in_map.x << ", " << in_map.y << "\n";
    vec2<float, WindowSpace> in_window_again = SpaceConversions<float>::transform(in_map);
    std::cout << std::boolalpha << (in_window_again == in_window) << "\n";
    return 0;
}