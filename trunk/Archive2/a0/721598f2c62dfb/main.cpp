#include <vector>
#include <iterator>

class MyClass {
   std::vector<int> lst { 1, 3, 77, 42 };
public:
   struct const_iterator : public std::vector<int>::const_iterator {
       using base_type         = std::vector<int>::const_iterator;
       using iterator_type     = const_iterator;
       using iterator_category = std::forward_iterator_tag;

       using base_type::operator++;
       using base_type::operator*;
       const_iterator& operator+=(difference_type) = delete;
       const_iterator& operator-=(difference_type) = delete;
       const_iterator  operator+ (difference_type) = delete;
       const_iterator  operator- (difference_type) = delete;

       const_iterator(base_type it) : base_type(it) {}
   };

   template <typename it>
   struct range : std::pair<it,it> {
       range(it b, it e) : std::pair<it,it>(b,e) {}
       
       it begin() const { return this->first; }
       it end()   const { return this->second; }
   };

   range<const_iterator> getNumbers() const { return { lst.cbegin(), lst.cend() }; }
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
