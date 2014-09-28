#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

int main()
{
    const std::vector</* const */ std::string> v { "test", "goodbye" };

    auto convert = std::mem_fn(&std::string::c_str);

    const auto vc = [&]{
        std::vector<const char*> tmp(v.size());
        std::transform(v.begin(), v.end(), back_inserter(tmp), convert);
        return tmp;
    }();
}
