#include <memory>
#include <fstream>

int main()
{
    auto f = std::fstream{"foo.bar"};
    auto i = std::unique_ptr<int>{new int};

    return 0;
}
