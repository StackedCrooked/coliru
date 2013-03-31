#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

using Sentence = std::vector<std::string>;

class Compar
{
    public:
    Compar(float epsilon = std::numeric_limits<float>::epsilon()):
    epsilon(epsilon)
    {
        }

bool equal(std::vector<float> a, std::vector<float> b)
{
    return std::equal(a.begin(), a.end(), b.begin(), mypredicate(epsilon));
}

private:
float epsilon;
    struct mypredicate {
        mypredicate(float epsilon) : epsilon_(epsilon) {}
        bool operator() (float i, float j)
{
    float diff = std::fabs(i-j);
    return diff < epsilon_;
}
        float epsilon_;
    };
};


int main()
{
//    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };
//    std::cout << sentence << std::endl;
}
