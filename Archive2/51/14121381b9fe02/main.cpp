#include <type_traits>
#include <iterator>
#include <vector>

template<class T>
struct A {
    template<class InputIterator>
    typename std::enable_if<
        std::is_base_of<std::input_iterator_tag,
                        typename std::iterator_traits<InputIterator>::iterator_category>::value,
    void>::type assign(InputIterator first, InputIterator last);
};

int main() {
    std::vector<int> v;
    
    A<int> a;
    a.assign(v.begin(), v.end());
}