#include <vector>
#include <functional>
#include <algorithm>

struct MyType {
    int field;
};


template <typename F>
struct CompareBy {
    explicit CompareBy(F&& f) : f(std::forward<F>(f)) {}
    template <typename U, typename V> 
        bool  operator()(U const& u, V const& v) const {
            return f(u) < f(v);
        }

  private:
    F f;
};

template <typename F>
CompareBy<F> compare_by(F&& f) { return CompareBy<F>(std::forward<F>(f)); }

int main()
{
    std::vector<MyType> vec;

    auto m = std::max_element(std::begin(vec), std::end(vec), compare_by(std::mem_fn(&MyType::field)));
}
