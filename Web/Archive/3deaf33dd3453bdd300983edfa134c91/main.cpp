#include <memory>

void foo2(int) {}

int main()
{
    int a = 0;
    std::shared_ptr<void*> ptr(nullptr, [&](void*){foo2(a); });
}
