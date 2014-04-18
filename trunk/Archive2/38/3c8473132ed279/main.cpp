#include <valarray>

int main()
{
    std::valarray<bool> a(500),b(500),c(500);
    c = b ^ a;
}