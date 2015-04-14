#include<iterator>

template<class F>
auto fails_to_compile(long, F&&) -> std::true_type { return std::true_type{}; }

template<class F>
auto fails_to_compile(int, F&& f) -> decltype(f(), std::false_type()) { f(); return std::false_type{}; };

template<class F>
auto fails_to_compile(F&& f) -> decltype(fails_to_compile(0, std::forward<F>(f))) { return fails_to_compile(0, std::forward<F>(f)); }

struct test {

    template <class It>
    void foo(It i)
    {
        std::reverse_iterator<It> r = i;
    }

    void operator()() {
        const char s[] = "123";
        foo(s);
    }
};

int main()
{
    static_assert(decltype(fails_to_compile(test())){}, "");
}