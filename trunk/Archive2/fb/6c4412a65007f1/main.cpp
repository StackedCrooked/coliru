#include <vector>
#include <memory>
#include <algorithm>

class P
{
public:
    std::vector<int> a;
	std::unique_ptr<int> b;
};

int main()
{
    P p;
    P p2(std::move(p));
}