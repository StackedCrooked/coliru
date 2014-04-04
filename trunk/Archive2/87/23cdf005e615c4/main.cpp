#include <vector>
#include <boost/range/adaptors.hpp>

struct SliceLayerPart {
    int baz;
};

struct foo {
    std::vector<int> polyOrder;
};

struct bar {
    std::vector<SliceLayerPart> parts;
};

int main() {
    using boost::adaptors::transformed;

    foo partOrderOptimizer = {{1,2,0,3}};
    bar b{std::vector<SliceLayerPart>(4)};
    auto const layer = &b;

    auto lookup = [&](int i) -> SliceLayerPart& {
        return layer->parts[i];
    };

    for (auto&& part : partOrderOptimizer.polyOrder | transformed(lookup)) {
        std::cout << &part << '\n';
    }
}
