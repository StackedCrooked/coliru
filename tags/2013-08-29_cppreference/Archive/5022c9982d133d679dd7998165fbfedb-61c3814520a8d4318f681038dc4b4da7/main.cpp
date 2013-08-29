#include <vector>

template<typename iter, typename F>
void doit(iter begin, iter end, F f, int some_int) {
}

template<typename range, typename F>
void doit(range rng, F f, int some_int) {
}

int main()
{
    std::vector<int> v {1,2,3};
    doit(v, [] () {}, 23);
    doit(v.begin(), v.end(), [] () {}, 23);
}