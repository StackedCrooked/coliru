struct not_assignable
{
    not_assignable() = default;
    not_assignable(not_assignable const&) = default;
    not_assignable& operator=(not_assignable const&) = delete;
};

#include <vector>
#include <iterator>

int main()
{
    std::vector<not_assignable> vna;
    not_assignable n;
    //std::copy(&n, &n+1, std::back_inserter(vna));
    std::copy(&n, &n+1, std::inserter(vna, vna.end()));
}