#include <mutex>

std::mutex make_mutex() { return {}; }

struct brick {
public:
    brick(int x) : x(x) {}
    
    brick(brick const&) = delete;
    brick(brick&&) = delete;
private:
    int x;
};

brick make_brick(int x) { return { x }; }

int main() {
    auto&& m = make_mutex();
    auto&& b = make_brick(42);
}