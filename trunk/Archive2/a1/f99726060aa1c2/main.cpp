#include <atomic>

struct S
{
    int x;
    int y;
};

int main()
{
    std::atomic<S> asd;
    asd.store({1,2});
}
