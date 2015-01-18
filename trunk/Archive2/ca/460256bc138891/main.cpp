#include <algorithm>
#include <iostream>
#include <iterator>

template <typename T, typename S = short> class range_T {
    const T m_begin, m_end; const S m_step;
public:
    class RangeIterator : public std::iterator<std::input_iterator_tag, T> {
        T m_current; const T m_end; const S& m_step;
        const T& clip(const T& value) const {return m_step >= 0 ? std::min(value, m_end) : std::max(value, m_end);}
    public:
        RangeIterator(const T& current, const T& end, const S& step) : m_current(current), m_end(end), m_step(step) {m_current = clip(m_current);}
        RangeIterator& operator++() {m_current = clip(m_current + m_step); return *this;}
        RangeIterator operator++(int) {RangeIterator tmp(m_current, m_end, m_step); m_current = clip(m_current + m_step); return tmp;}
        bool operator==(const RangeIterator& rhs) {return m_current == rhs.m_current;}
        bool operator!=(const RangeIterator& rhs) {return m_current != rhs.m_current;}
        const T& operator*() const {return m_current;}
    };
    range_T(const T& end) : m_begin(0), m_end(end), m_step(1) {}
    range_T(const T& begin, const T& end, S step = 1) : m_begin(begin), m_end(end), m_step(step) {}
    RangeIterator begin() const { return RangeIterator(m_begin, m_end, m_step); }
    RangeIterator end() const { return RangeIterator(m_end, m_end, m_step); }
};
template <typename T, typename S = short> auto range(const T& b, const T& e, S s = 1) {return range_T<T, S>(b, e, s);}
template <typename T> auto range(const T& e) {return range_T<T, short>(0, e, 1);}

int main()
{
    std::cout << "Test..." << std::endl;

    for (auto i : range('a', char('z' + 1)))
        std::cout << i << std::endl;

    for (auto i : range(5)) {
        for (auto j : range(i + 1))
            std::cout << j << " ";
        std::cout << std::endl;
    }
    
    for (auto i : range(5, 10))
        std::cout << i << std::endl;

    for (auto i : range(9, -1, -1))
        std::cout << i << std::endl;

    for (auto i : range(0, 10, 2UL))
        std::cout << i << std::endl;

    for (auto i : range(8, -1, -2))
        std::cout << i << std::endl;
        
    std::cout << "done!" << std::endl;
}
