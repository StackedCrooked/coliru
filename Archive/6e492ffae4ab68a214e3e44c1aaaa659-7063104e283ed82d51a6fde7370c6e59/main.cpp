#ifndef MISC_XRANGE_HPP
#define MISC_XRANGE_HPP

#include <iterator>

template<typename T>
class xrange_t {
private:
    T begin_t, end_t, step_t;
    int step_end;
    using iter = std::iterator<std::random_access_iterator_tag,T>;
public:
    using range_type = T;
    xrange_t(T begin, T end, T step = 1): begin_t(begin), end_t(end), step_t(step) {
        step_end = (end_t-begin_t)/step_t;
        if(begin_t + step_end*step_t != end_t)
            ++step_end;
    }
    class iterator : iter {
    private:
        T value, step;
        xrange_t& range;
    public:
        iterator(T start, xrange_t& other): step(start), range(other) {
            value = range.begin_t + step * range.step_t;
        }
        T operator*() {
            return value;
        }
        const iterator& operator++() {
            value += range.step_t;
            ++step;
            return *this;
        }
        const iterator operator++(int) {
            iterator copy(*this);
            ++(*this);
            return copy;
        }
        const iterator& operator--() {
            value -= range.step_t;
            --step;
            return *this;
        }
        const iterator operator--(int) {
            iterator copy(*this);
            ++(*this);
            return copy;
        }
        iterator operator+(T st) {
            iterator copy(*this);
            copy.step += st;
            copy.value += (st * range.step_t);
            return copy;
        }
        iterator operator-(T st) {
            iterator copy(*this);
            copy.step -= st;
            copy.value -= (st * range.step_t);
            return copy;
        }
        bool operator==(const iterator& other) const {
            return step == other.step;
        }
        bool operator!=(const iterator& other) const {
            return step != other.step;
        }
    };

    iterator begin() {
        return iterator(0,*this);
    }
    iterator end() {
        return iterator(step_end,*this);
    }
    size_t size() const {
        if(step_end < 0)
            return 0;
        return step_end;
    }
};

template<typename T>
auto xrange(T begin, T end, T step) -> decltype(xrange_t<T>(begin,end,step)) {
    return xrange_t<T>(begin,end,step);
}

template<typename T>
auto xrange(T begin, T end) -> decltype(xrange_t<T>(begin,end,1)) {
    return xrange_t<T>(begin,end,1);
}

template<typename T>
xrange_t<T> xrange(T end) {
    return xrange_t<T>(1,end,1);
}

#ifndef NO_VECTOR_RANGE
#include <vector>

template<typename T>
std::vector<T> range(T begin, T end, T step) {
    auto range_t = xrange(begin,end,step);
    std::vector<T> vec;
    vec.reserve(range_t.size());
    for(auto&& i : range_t)
        vec.push_back(i);
    return vec;
}

template<typename T>
std::vector<T> range(T begin, T end) {
    auto range_t = xrange(begin,end,1);
    std::vector<T> vec;
    vec.reserve(range_t.size());
    for(auto&& i : range_t)
        vec.push_back(i);
    return vec;
}

template<typename T>
std::vector<T> range(T end) {
    auto range_t = xrange(1,end,1);
    std::vector<T> vec;
    vec.reserve(range_t.size());
    for(auto&& i : range_t)
        vec.push_back(i);
    return vec;
}

#endif //NO_VECTOR_RANGE
#endif //MISC_XRANGE_HPP