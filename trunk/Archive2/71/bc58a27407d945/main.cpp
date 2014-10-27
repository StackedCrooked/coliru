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

struct WindowSpace {};
struct MapSpace {};
struct CameraSpace {};

namespace detail {
    // Generic versions
    // Anything -> Window
    template<typename T, typename InSpace>
    vec2<T, WindowSpace> transform(vec2<T, InSpace> in, InSpace, WindowSpace);
    
    // Anything -> Camera
    template<typename T, typename InSpace>
    vec2<T, CameraSpace> transform(vec2<T, InSpace> in, InSpace, CameraSpace);
    
    // Anything -> Map
    template<typename T, typename InSpace>
    vec2<T, MapSpace> transform(vec2<T, InSpace> in, InSpace, MapSpace);
    
    
    // Specializations
    // Map -> Window
    template<typename T>
    vec2<T, WindowSpace> transform(vec2<T, MapSpace> in, MapSpace, WindowSpace) {
        return { in.x * 2, in.y * 2};
    }
    
    // Window -> Map
    template<typename T>
    vec2<T, MapSpace> transform(vec2<T, WindowSpace> in, WindowSpace, MapSpace) {
        return { in.x/2, in.y/2 };
    }
    
    // Window -> Camera
    template<typename T>
    vec2<T, CameraSpace> transform(vec2<T, WindowSpace> in, WindowSpace, CameraSpace) {
        return { -in.x, -in.y };
    }
    
};


template<typename OutSpace, typename T, typename InSpace> vec2<T, OutSpace> transform(vec2<T, InSpace> in) {
    return detail::transform(in, InSpace(), OutSpace());
}

int main() {
    vec2<float, WindowSpace> in_window = {20.0f, 80.0f};
    std::cout << in_window.x << ", " << in_window.y << "\n";
    
    auto in_map = transform<MapSpace>(in_window);
    std::cout << in_map.x << ", " << in_map.y << "\n";
    
    auto in_window_again = transform<WindowSpace>(in_map);
    std::cout << std::boolalpha << (in_window_again == in_window) << "\n";
    
    return 0;
}