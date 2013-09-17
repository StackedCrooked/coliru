#include <boost/multi_array.hpp>

class Test {
    typedef boost::multi_array<double, 2> array_type;
    array_type data;

    public:
        Test() {
            data.reshape(boost::extents[2048][2048]);
        }
};

int main() {
    std::cout << "Constructing\n";
    Test t;
    std::cout << "Done\n";
}
