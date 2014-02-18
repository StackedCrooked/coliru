#include <memory>
#include <vector>

struct deleter {
    deleter() : c(*"") {}
    void operator () (int *) const {}
    const char& c;
};

int main() {
    std::vector<std::unique_ptr<int, deleter>> vec;
    vec.push_back(std::unique_ptr<int, deleter>{new int(42)});
    vec[0] = std::unique_ptr<int, deleter>{new int(42)};
}
