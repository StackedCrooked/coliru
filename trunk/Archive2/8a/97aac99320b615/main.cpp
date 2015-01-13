#include <boost/polygon/voronoi_diagram.hpp>

template <typename T>
struct yay { 
    boost::polygon::voronoi_diagram<T> diagram;
};

int main() {
    yay<double> object;
}
