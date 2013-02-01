//http://chat.stackoverflow.com/transcript/message/7478862#7478862
//Crowz: How could one iterate a 2dimensional array diagonally?

#include <iterator>
#include <type_traits>
#include <iostream>
template<class container_type>
struct diag_iterator {
    typedef int difference_type;
    typedef decltype(std::declval<container_type>()[0][0]) reference;
    typedef typename std::remove_reference<reference>::type value_type;
    typedef value_type* pointer;
    typedef std::forward_iterator_tag iterator_category;
    
    diag_iterator(container_type& cont, int max_x, int max_y, bool begin=true) 
    : c(&cont), x(0), y(0), maxx(max_x), maxy(max_y) {
        if (!begin) {
            x = maxx;
            y = maxy;
        }
    }
    diag_iterator operator++(int) {diag_iterator t(*this); ++*this; return t;}
    reference operator*() const {return (*c)[x][y];}
    friend bool operator==(const diag_iterator& lhs, const diag_iterator& rhs) {return lhs.c==rhs.c && lhs.x==rhs.x && lhs.y==rhs.y;}
    friend bool operator!=(const diag_iterator& lhs, const diag_iterator& rhs) {return lhs.c!=rhs.c || lhs.x!=rhs.x || lhs.y!=rhs.y;} 
    diag_iterator& operator++() {
        if (x) {
            --x;
            ++y;
            if (y >= maxy) {
                x += y+1;
                y = 0;
                if (x >= maxx) {
                    y = x - maxx+1;
                    x = maxx-1;
                }
            }
        } else {
            x = y+1;
            y = 0;
            if (x >= maxx) {
                y = x - maxx+1;
                x = maxx-1;
            }
        }
        return *this;
    }
private:
    container_type* c;
    int x, y;
    int maxx, maxy;
};
template<class container_type>
diag_iterator<container_type> make_diag(container_type& cont, int max_x, int max_y, bool begin=true)
{return diag_iterator<container_type>(cont, max_x, max_y, begin);}

template<typename T, std::size_t N, std::size_t M>
diag_iterator<T[N][M]> make_diag(T(&arr)[N][M], bool begin = true) {
    return make_diag(arr, N, M, begin);
}

#include <array>
int main() {
    {
        int giveup = 12;
        int array[3][4] = {{0, 2, 5, 8},
                           {1, 4, 7,10}, 
                           {3, 6, 9,11}};    
        auto last = make_diag(array, false);
        for (auto first=make_diag(array, true); first!=last && giveup-->0; ++first) 
            std::cout << *first << '\n';
    }
    std::cout << '\n';
    {
        int giveup = 12;
        int array[4][3] = {{0, 2, 5},
                           {1, 4, 8}, 
                           {3, 7,10},
                           {6, 9,11}};    
        auto last = make_diag(array, false);
        for (auto first=make_diag(array, true); first!=last && giveup-->0; ++first) 
            std::cout << *first << '\n';
    }
    return 0;
}
