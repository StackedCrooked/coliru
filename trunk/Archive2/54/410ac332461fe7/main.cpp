#include <memory>
#include <cstdio>

struct foo
{
    foo()
    {
        puts("foo constructed");
    }

    ~foo()
    {
        puts("foo destroyed");
    }
};

int main(int, char**)
{
    auto sp1 = std::make_shared<foo>();
    printf("sp1.use_count() == %ld\n", sp1.use_count());
    {
        auto sp2(sp1);
        printf("sp1.use_count() == %ld\n", sp1.use_count());
        {
            auto sp3 = sp1;
            printf("sp1.use_count() == %ld\n", sp1.use_count());
        }
        printf("sp1.use_count() == %ld\n", sp1.use_count());
    }
    printf("sp1.use_count() == %ld\n", sp1.use_count());
}
