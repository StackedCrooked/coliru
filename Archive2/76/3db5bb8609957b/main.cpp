#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <memory>

using namespace std;

class object {};
enum  render { opengl, gdi, directx };
shared_ptr< function<void (object&)> > plugin(render r) {
    switch (r) {
    case render::opengl: return std::make_shared<function<void (object&)>>([](object&){});
    case render::gdi: return std::make_shared<function<void (object&)>>([](object&){});
    case render::directx: return std::make_shared<function<void (object&)>>([](object&){});
    default: return std::make_shared<function<void (object&)>>([](object&){});
    }
}

int main() {
    auto v = vector<unsigned int>(1000);
    generate(begin(v), end(v), mt19937{random_device{}()});
    auto median = begin(v) + v.size() / 2;
    nth_element(begin(v), median, end(v));

    auto o = plugin( render::opengl );
    auto g = plugin( render::gdi );
    auto d = plugin( render::directx );
}