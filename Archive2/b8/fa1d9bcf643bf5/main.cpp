void g() noexcept {}

template <typename Func>
void f(Func && func) noexcept(noexcept(func()))
{ static_assert(noexcept(func()), "func()"); } // No error!

void h() { f(&g); } // No error!

static_assert(noexcept(f(&g)), "Error!");

int main() {}