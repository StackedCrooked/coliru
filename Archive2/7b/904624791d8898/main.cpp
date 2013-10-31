#include <utility>

struct Result { Result(); explicit Result(Result&&) noexcept; Result(const Result&); };

int main() {
    Result r;
    auto x = std::move(r);
    (void)x;
}
