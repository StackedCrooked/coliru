#include <vector>
#include <deque>
using namespace std;

struct NoCopyNoMove
{
    NoCopyNoMove(const NoCopyNoMove&) = delete;
    NoCopyNoMove& operator=(const NoCopyNoMove&) = delete;
    NoCopyNoMove(NoCopyNoMove&&) = delete;
    NoCopyNoMove& operator=(NoCopyNoMove&&) = delete;

    NoCopyNoMove(int){};
};

struct OnlyMove
{
    OnlyMove(const OnlyMove&) = delete;
    OnlyMove& operator=(const OnlyMove&) = delete;
    OnlyMove(OnlyMove&&) noexcept {}
    OnlyMove& operator=(OnlyMove&&) noexcept {}

    OnlyMove(int){};
};

int main()
{
    deque<NoCopyNoMove> x;
    x.emplace_back(1);

    vector<OnlyMove> y;
    y.emplace_back(1);
}