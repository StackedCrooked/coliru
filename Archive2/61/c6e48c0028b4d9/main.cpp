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



#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include <chrono>

int main(int argc, char** argv) {
    std::mt19937_64 el(time(0));
    std::vector<int> v;
    
    int size = 10000000;
    int chunk_size = size;
    
    for (int i = 0; i < size; ++i) v.push_back(i);
    std::shuffle(v.begin(), v.end(), el);
    
    
    std::cout << "std::sort unsorted: ";
    std::vector<int> v_std = v;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += chunk_size) {
        std::sort(v_std.begin() + i, v_std.begin() + i + chunk_size);
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    
    
    std::cout << "introsort unsorted: ";
    std::vector<int> v_intro = v;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += chunk_size) {
        introsort(v_intro.begin() + i, v_intro.begin() + i + chunk_size);
    }
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    
    
    std::cout << "std::sort sorted: ";
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += chunk_size) {
        std::sort(v_std.begin() + i, v_std.begin() + i + chunk_size);
    }
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    
    
    std::cout << "introsort sorted: ";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += chunk_size) {
        introsort(v_intro.begin() + i, v_intro.begin() + i + chunk_size);
    }
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    
    return 0;
}