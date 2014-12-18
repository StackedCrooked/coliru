#include <initializer_list>
#include <iostream>
#include <array>
struct bob
{
 int i,j,k,l,m,n,o,p;
 constexpr int foo(){ return i;};
};
//constexpr int max(const std::initializer_list<int>& ints)
constexpr int max(const std::initializer_list<int> ints)
{
        return ints.size();
}
constexpr int max2(bob ints)
{
        // return ints.i;
        return ints.foo();
}

constexpr int max(int i)
{
     return i;
}
int main()
{
        constexpr int z = max({7,6,5,4,3,2,1});
        constexpr int z2 = max({5,4,3,2,1});
        //static_assert(z == 7, "");
        //static_assert(z2 == 5, "");
        std::cout << z << "   "<<z2<<std::endl;

        constexpr int y = max(7);
        constexpr int y2 = max(5);
        std::cout << y << "   "<<y2<<std::endl;

        constexpr int q = max2({7,6,5,4,3,2,1});
        constexpr int q2 = max2({5,4,3,2,1,1,1});
        std::cout << q << "   "<<q2<<std::endl;

}
