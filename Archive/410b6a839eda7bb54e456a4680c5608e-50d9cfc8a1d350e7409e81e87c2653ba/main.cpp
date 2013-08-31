#include <memory>

struct move_only {
    move_only() = default;
    move_only(move_only const&) = delete;
    move_only(move_only&&) = default;
    
    void foo() {}
};

int main()
{
    auto p = std::bind(&move_only::foo, move_only {});
    auto q = std::move(p);
}