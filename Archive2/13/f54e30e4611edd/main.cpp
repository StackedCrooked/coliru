#include <list>

class Nums
{
    static std::list<int> nums;
public:
    Nums() {}
    static void append(int i) {
        nums.push_back(i);
    }
};

std::list<int> Nums::nums;

int main()
{
    Nums::append(1);
}
