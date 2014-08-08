#include <boost/optional.hpp>
#include <boost/utility/typed_in_place_factory.hpp>
#include <array>
#include <vector>

struct vec {
    std::vector<int> v;
    vec(int s) {
        v.reserve(s);
    }
};

int main() {
    boost::optional<int> x;
    x = boost::in_place<vec, int>(1000);
}
