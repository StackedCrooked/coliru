#include <iostream>
#include <vector>

template<std::size_t IN>
class Net {
public:
    int i = 7;
};

template<std::size_t IN>
Net<IN> make_net() {
    return Net<IN>();
}

int main() {
    Net<2> a_net = make_net<2>();
    std::cout << "net i = " << a_net.i << std::endl;
}
