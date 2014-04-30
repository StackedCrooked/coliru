#include <tuple>
#include <utility>

int main()
{
    std::tuple<int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int> t243;
    auto x = std::move(t243);
}
