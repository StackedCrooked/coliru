#include <algorithm>

template <typename T>
struct Anim
{
    Anim(T length) noexcept  : cur_(0), length_(length) {}

    inline void step() noexcept { cur_ = std::min(cur_ + 1, length_); }
    inline T cur() const noexcept { return cur_; }
    bool done() const noexcept { return cur_ == length_; }
private:
    T cur_;
    T length_;
};