#include <vector>
#include <iterator>

namespace detail {
    template <typename Base>
    struct const_forward_iterator : public Base {
        using base_type         = Base;
        using iterator_type     = const_forward_iterator;
        using iterator_category = std::forward_iterator_tag;

        const_forward_iterator& operator+=(typename Base::difference_type) = delete;
        const_forward_iterator& operator-=(typename Base::difference_type) = delete;
        const_forward_iterator  operator+ (typename Base::difference_type) = delete;
        const_forward_iterator  operator- (typename Base::difference_type) = delete;

        const_forward_iterator(base_type it) : base_type(it) {}
    };

    template <typename it>
    struct range : std::pair<it,it> {
        range(it b, it e) : std::pair<it,it>(b,e) {}

        it begin() const { return this->first; }
        it end()   const { return this->second; }
    };
}

class MyClass {
    std::vector<int> lst { 1, 3, 77, 42 };
  public:
    
    using iterator_type = detail::const_forward_iterator<std::vector<int>::const_iterator>;

    detail::range<iterator_type> getNumbers() const { return { lst.cbegin(), lst.cend() }; }
};

#include <iostream>

int main()
{
    MyClass o;

    for (auto i : o.getNumbers())
        std::cout << i << " ";

    auto numbers = o.getNumbers();
    //numbers.first += 2; error: use of deleted function
}
