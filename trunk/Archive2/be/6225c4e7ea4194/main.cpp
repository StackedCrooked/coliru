#include <future>

struct CopyOnly {
    CopyOnly() = default;
    CopyOnly(const CopyOnly&) = default;
    CopyOnly& operator=(const CopyOnly&) = default; 

    void operator()() {}
};

int main()
{
    CopyOnly co;
    std::packaged_task<void()>{co};
}
