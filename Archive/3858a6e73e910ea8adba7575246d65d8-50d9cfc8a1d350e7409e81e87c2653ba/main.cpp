#include <vector>

struct CanNotCopy {
  int& intref_;
  CanNotCopy(int& i) noexcept : intref_(i) {}
};

int main()
{
    std::vector<CanNotCopy> v;
    int i = 0;
    v.emplace_back(i);
}