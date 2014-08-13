#include <vector>
#include <iterator>
#include <stdexcept>
#include <random>
#include <utility>


// returns an iterator pointing to a random element from the given sequence
template<class Iter, class URNG>
Iter random_choice(Iter first, Iter last, URNG&& g);

// selects k samples without replacement from the given sequence
// the order of the samples in the output is undefined, but not necessarily random
template<class InIter, class OutIter, class URNG>
void random_sample(InIter first, InIter last, OutIter out, int k, URNG&& g);


namespace detail {
    template<class Iter, class URNG>
    Iter random_choice(Iter first, Iter last, URNG&& g, std::random_access_iterator_tag) {
        auto size = last - first;
        return first + std::uniform_int_distribution<decltype(size)>(0, size - 1)(g);
    }

    template<class Iter, class URNG>
    Iter random_choice(Iter first, Iter last, URNG&& g, std::forward_iterator_tag) {
        typedef typename std::iterator_traits<Iter>::difference_type diff_t;

        Iter result = first++;
        for (diff_t i = 1; first != last; ++i, ++first) {
            if (std::uniform_int_distribution<diff_t>(0, i)(g) == 0) result = first;
        }

        return result;
    }
}

template<class Iter, class URNG>
Iter random_choice(Iter first, Iter last, URNG&& g) {
    if (first == last) throw std::out_of_range("empty sequence passed to random_choice");

    return detail::random_choice(first, last, g, typename std::iterator_traits<Iter>::iterator_category());
}

template<class InIter, class OutIter, class URNG>
void random_sample(InIter first, InIter last, OutIter out, int k, URNG&& g) {
    typedef typename std::iterator_traits<InIter>::value_type T;
    typedef typename std::iterator_traits<InIter>::difference_type diff_t;

    std::vector<T> reservoir;
    reservoir.reserve(k);

    for (diff_t i = 0; i < k; ++i, ++first) {
        if (first == last) throw std::out_of_range("k larger than sequence size passed to random_sample");
        reservoir.push_back(*first);
    }

    for (diff_t i = k; first != last; ++i, ++first) {
        diff_t j = std::uniform_int_distribution<diff_t>(0, i)(g);
        if (j < k) reservoir[j] = *first;
    }

    for (auto& e : reservoir) *out++ = std::move(e);
}


#include <array>
#include <iostream>

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 rng(rd());
    
    std::array<int, 7> x = { 2, 3, 5, 7, 11, 13, 17};
    
    // choose and print a random element from x 5 times
    for (int i = 0; i < 5; ++i) std::cout << *random_choice(x.begin(), x.end(), rng) << "\n";
    
    // choose a random sample of 3 elements from x and print them 5 times
    for (int i = 0; i < 5; ++i) {
        std::array<int, 3> out;
        random_sample(x.begin(), x.end(), out.begin(), 3, rng);
        
        for (auto& e : out) std::cout << e << " ";
        std::cout << "\n";
    }
    
    return 0;
}