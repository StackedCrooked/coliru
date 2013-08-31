#include <iterator>
#include <cassert>
#include <functional>
#include <iostream>

template<class iterator_type, class cmp_type=std::less<typename std::iterator_traits<iterator_type>::value_type>>
void qs (iterator_type first, iterator_type last, cmp_type&& cmp=cmp_type()) {
    using std::swap;
    if (first==last) return;
    iterator_type left=std::next(first);
    if (left==last) return;
    iterator_type right=last;
    for(;;) {
        while (left!=right && cmp(*left, *first))
            ++left;
        if (left==right) {
            --left;
            break;
        }
        --right;
        while (left!=right && cmp(*first,*right))
            --right;
        if (left!=right) {
            swap(*left, *right);
            ++left;
        }
        else {
            --left;
            break;
        }
    }
    if (first!=left) {
        swap(*first, *left);
        qs(first, left, std::forward<cmp_type>(cmp));
    }
    if (right != last) 
        qs(right, last, std::forward<cmp_type>(cmp));        
}






#include <iostream>
#include <algorithm>
struct Point {double x,y;};
bool operator<(const Point&lhs, const Point&rhs) {if(lhs.y!=rhs.y)return lhs.y<rhs.y; return lhs.x<rhs.x;}
std::ostream& operator<<(std::ostream&o, const Point& p) {return o<<'('<<p.x<<','<<p.y<<')';}

void test(std::initializer_list<int> init) {
    std::cerr << "TESTING ";
    std::copy(std::begin(init),std::end(init),std::ostream_iterator<int>(std::cerr));
    std::vector<int> arr(init);
    qs(std::begin(arr),std::end(arr));
    if (std::is_sorted(std::begin(arr),std::end(arr)) == false) {
        std::cerr << " FAILED ";
        std::copy(std::begin(arr),std::end(arr),std::ostream_iterator<int>(std::cerr));
    } 
    std::cerr << "\n";
}

int main() {
    test({0});
    test({0,0});
    test({0,1});
    test({1,0});
    test({0,0,0});
    test({0,0,1});
    test({0,1,0});
    test({1,0,0});
    test({0,1,1});
    test({1,0,1});
    test({1,1,0});
    test({0,1,2});
    test({0,2,1});
    test({1,0,2});
    test({1,2,0});
    test({2,0,1});
    test({2,1,0});
    
    std::array<Point,5> arr ={{{2.32, 23}, {-21, 23}, {-65, 34}, {34, -11}, {21, -22}}};
    qs(std::begin(arr),std::end(arr));
    std::copy(std::begin(arr),std::end(arr),std::ostream_iterator<Point>(std::cout));
}