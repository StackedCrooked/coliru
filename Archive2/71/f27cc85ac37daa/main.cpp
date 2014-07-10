#ifndef INTROSORT_H
#define INTROSORT_H

#include <iterator>
#include <utility>
#include <algorithm>

#if __cplusplus >= 201103L
    #define PREFER_MOVE(x) std::move(x)
#else
    #define PREFER_MOVE(x) (x)
#endif


namespace detail {
    namespace introsort {
        using std::swap;

        enum { INSERTION_SORT_THRESHOLD = 24 };

        // floor(log2(n)), used to compute maximum recursion depth for n > 0
        template<class T>
        T log2(T n) {
            T log = 0;

            while (n >= 1) {
                ++log;
                n >>= 1;
            }

            return log - 1;
        }

        // two insertion sort implementations, one with a bound check, one assuming a sentinel element
        template<class Iter, class Compare>
        void insertion_sort_unguarded(Iter begin, Iter end, Compare comp) {
            if (begin == end) return;

            for (Iter cur = begin + 1; cur != end; ++cur) {
                typename std::iterator_traits<Iter>::value_type tmp(PREFER_MOVE(*cur));

                Iter sift;
                for (sift = cur; comp(tmp, *(sift - 1)); --sift) {
                    *sift = PREFER_MOVE(*(sift - 1));
                }

                *sift = PREFER_MOVE(tmp);
            }
        }
        
        template<class Iter, class Compare>
        void insertion_sort(Iter begin, Iter end, Compare comp) {
            if (begin == end) return;

            for (Iter cur = begin + 1; cur != end; ++cur) {
                typename std::iterator_traits<Iter>::value_type tmp(PREFER_MOVE(*cur));

                Iter sift;
                for (sift = cur; sift != begin && comp(tmp, *(sift - 1)); --sift) {
                    *sift = PREFER_MOVE(*(sift - 1));
                }

                *sift = PREFER_MOVE(tmp);
            }
        }

        // moves the median of a, b and c into res
        template<class Iter, class Compare>
        void get_median(Iter res, Iter a, Iter b, Iter c, Compare comp) {
            if (comp(*a, *b)) {
                if (comp(*b, *c)) swap(*res, *b);
                else if (comp(*a, *c)) swap(*res, *c);
                else swap(*res, *a);
            } else {
                if (comp(*a, *c)) swap(*res, *a);
                else if (comp(*b, *c)) swap(*res, *c);
                else swap(*res, *b);
            }
        }

        template<class Iter, class Compare>
        Iter unguarded_partition(Iter begin, Iter end, Compare comp) {
            // move pivot into local for speed
            typename std::iterator_traits<Iter>::value_type pivot(PREFER_MOVE(*begin));

            Iter first = begin;
            Iter last = end;

            // partition
            while (true) {
                while (comp(*++first, pivot));
                while (comp(pivot, *--last));
                if (first >= last) break;
                swap(*first, *last);
            }
            
            // put pivot in place
            Iter pivot_pos = first - 1;
            *begin = PREFER_MOVE(*pivot_pos);
            *pivot_pos = PREFER_MOVE(pivot);

            return pivot_pos;
        }

        template<class Iter, class Compare>
        void introsort_loop(Iter begin, Iter end, int depth_limit, Compare comp) {
            typedef typename std::iterator_traits<Iter>::difference_type diff_t;

            while (depth_limit) {
                diff_t size = end - begin;
                if (size <= INSERTION_SORT_THRESHOLD) return;

                get_median(begin, begin + 1, begin + size / 2, end - 1, comp);
                Iter pivot_pos = unguarded_partition(begin, end, comp);

                --depth_limit;
                //introsort_loop(begin, pivot_pos, depth_limit, comp);
                //begin = pivot_pos + 1;
                introsort_loop(pivot_pos + 1, end, depth_limit, comp);
                end = pivot_pos;
            }

            // we have reached the depth limit, we've likely hit a worst case
            // use heapsort on what's left
            std::make_heap(begin, end);
            std::sort_heap(begin, end);
        }

        template<class Iter, class Compare>
        void introsort(Iter begin, Iter end, Compare comp) {
            typename std::iterator_traits<Iter>::difference_type size = end - begin;

            if (size > INSERTION_SORT_THRESHOLD) {
                introsort_loop(begin, end, 2*log2(size), comp);
                insertion_sort(begin, begin + INSERTION_SORT_THRESHOLD + 1, comp);
                insertion_sort_unguarded(begin + INSERTION_SORT_THRESHOLD, end, comp);
            } else insertion_sort(begin, end, comp);
        }

        template<class Iter>
        void introsort(Iter begin, Iter end) {
            introsort(begin, end, std::less<typename std::iterator_traits<Iter>::value_type>());
        }
    }
}

using detail::introsort::introsort;

#undef PREFER_MOVE

#endif



#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <chrono>

int copies = 0;
int moves = 0;
int swaps = 0;
int compares = 0;
int array_accesses = 0;

void print_stats() {
    std::cout << "compares: " << compares << "\n";
    std::cout << "moves: " << moves << "\n";
    std::cout << "array_accesses: " << array_accesses << "\n";
    if (copies) std::cout << "copies: " << copies << "\n";
    if (swaps) std::cout << "swaps: " << swaps << "\n";
}

void clear_stats() {
    copies = 0;
    moves = 0;
    swaps = 0;
    compares = 0;
    array_accesses = 0;
}

struct A {
    A(int x) : x(x) {}
    A(const A& a) : x(a.x) { ++copies; }
    A(const A&& a) : x(a.x) { ++moves; }
    A& operator=(const A& a) { x = a.x; ++copies; return *this; }
    A& operator=(const A&& a) { x = a.x; ++moves; return *this; }

    int x;
};

struct I {
    std::vector<A>::iterator i;

    I() : i() {}
    I(std::vector<A>::iterator i) : i(i) {}
    I& operator+=(size_t n) { i += n; return *this; }
    I& operator-=(size_t n) { i -= n; return *this; }
    I operator+(size_t n) const { return i + n; }
    I operator-(size_t n) const { return i - n; }
    std::vector<A>::iterator::difference_type operator-(const I& x) const { return i - x.i; }
    A& operator*() { ++array_accesses; return *i; }
    A& operator*() const { ++array_accesses; return *i; }
    I& operator--() { --i; return *this; }
    I operator--(int) { I tmp = i; --i; return tmp; }
    I& operator++() { ++i; return *this; }
    I operator++(int) { I tmp = i; ++i; return tmp; }
};

bool operator==(const I& a, const I& b) { return a.i == b.i; }
bool operator<(const I& a, const I& b) { return a.i < b.i; }
bool operator>(const I& a, const I& b) { return a.i > b.i; }
bool operator!=(const I& a, const I& b) { return a.i != b.i; }
bool operator<=(const I& a, const I& b) { return a.i <= b.i; }
bool operator>=(const I& a, const I& b) { return a.i >= b.i; }

namespace std {
template<>
class iterator_traits<I> {
public:
    typedef  std::vector<A>::iterator::difference_type difference_type;
    typedef  std::vector<A>::iterator::value_type value_type;
    typedef  std::vector<A>::iterator::iterator_category iterator_category;
    typedef  std::vector<A>::iterator::reference reference;
};
}

bool operator==(const A& a, const A& b) { ++compares; return a.x == b.x; }
bool operator<(const A& a, const A& b) { ++compares; return a.x < b.x; }

#define I(x) (x)
#define A int
int main(int argc, char** argv) {
    std::mt19937_64 el(time(0));

     {
        std::vector<A> v;
        int y = 10000000;
        int chunk = y;
        for (int i = 0; i < y; ++i) {
            // // normalize to [-1,+1]
            // double x = (2.0 * (double)i / y) - 1.0;
            // // calculate x^5
            // double z = x * x * x * x * x;
            // // normalize to array size
            // double w = (z + 1.0) / 2.0 * y + 1;
            // // decrease resolution for more equal values
            // w /= 3.0;
            // v.push_back(int(w + 1));
        }
        for (int i = 0; i < y; ++i) v.push_back(i);

        std::shuffle(v.begin(), v.end(), el);

        std::cout << "introsort:\n";
        std::vector<A> v_intro = v;
        clear_stats();
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < y; i += chunk) {
            introsort(I(v_intro.begin() + i), I(v_intro.begin() + i + chunk));
        }
        auto end = std::chrono::high_resolution_clock::now();
        print_stats();
        std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
        std::cout << "\n";
        
        std::cout << "std_sort:\n";
        std::vector<A> v_std = v;
        clear_stats();
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < y; i += chunk) {
            std::sort(I(v_std.begin() + i), I(v_std.begin() + i + chunk));
        }
        end = std::chrono::high_resolution_clock::now();
        print_stats();
        std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
        std::cout << "\n";
        if (v_std != v_intro) std::cout << "INCORRECT!\n";

        std::cout << "introsort:\n";
        clear_stats();
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < y; i += chunk) {
            introsort(I(v_intro.begin() + i), I(v_intro.begin() + i + chunk));
        }
        end = std::chrono::high_resolution_clock::now();
        print_stats();
        std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
        std::cout << "\n";

        std::cout << "std_sort:\n";
        clear_stats();
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < y; i += chunk) {
            std::sort(I(v_std.begin() + i), I(v_std.begin() + i + chunk));
        }
        end = std::chrono::high_resolution_clock::now();
        print_stats();
        std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
        std::cout << "\n";
        if (v_std != v_intro) std::cout << "INCORRECT!\n";
    }


    return 0;
}
