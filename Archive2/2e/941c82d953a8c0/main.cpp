#include <iterator>
#include <algorithm>

std::size_t length(const std::string&s) {return s.length();}

namespace seqan {

template <typename It, typename F, typename T>
inline void prescan(It front, It back, F op, T const& id) {
    using namespace std;
    if (front == back) return;
    typename iterator_traits<It>::value_type accu = *front;
    *front++ = id;
    for (; front != back; ++front) {
        swap(*front, accu);
        accu = op(accu, *front);
    }
}

template <typename TIter, typename TSize, unsigned int RADIX>
inline void radix_permute(TIter front, TIter back, TSize (& bounds)[RADIX], TSize base) {
    for (TIter i = front; i != back; ++i)
        ++bounds[static_cast<unsigned int>((*i)[base])];

    TSize fronts[RADIX];

    std::copy(bounds, bounds + RADIX, fronts);
    prescan(fronts, fronts + RADIX, std::plus<TSize>(), 0);
    std::transform(bounds, bounds + RADIX, fronts, bounds, std::plus<TSize>());

    TSize active_base = 0;

    for (TIter i = front; i != back; ) {
        if (active_base == RADIX - 1)
            return;
        while (fronts[active_base] >= bounds[active_base])
            if (++active_base == RADIX - 1)
                return;
        TSize current_base = static_cast<unsigned int>((*i)[base]);
        if (current_base <= active_base)
            ++i;
        else
            std::iter_swap(i, front + fronts[current_base]);
        ++fronts[current_base];
    }
}

template <typename TIter, typename TSize>
inline void insertion_sort(TIter front, TIter back, TSize base) {
    //typedef typename Value<TIter>::Type T;
    typedef typename std::iterator_traits<TIter>::value_type T;
    struct {
        TSize base, len;
        bool operator ()(T const& a, T const& b) {
            for (TSize i = base; i < len; ++i)
                if (a[i] < b[i]) return true;
                else if (a[i] > b[i]) return false;
            return false;
        }
    } cmp = { base, length(*front) }; // No closures yet. :-(

    for (TIter i = front + 1; i != back; ++i) {
        T value = *i;
        TIter j = i;
        for ( ; j != front && cmp(value, *(j - 1)); --j)
            *j = *(j - 1);
        if (j != i)
            *j = value;
    }
}

template <typename TIter, typename TSize, unsigned int RADIX>
inline void radix(TIter top, TIter front, TIter back, TSize base, TSize (& parent_bounds)[RADIX], TSize next) {
    if (back - front > 1) {
        TSize bounds[RADIX] = { 0 };
        radix_permute(front, back, bounds, base);

        // Sort current bucket recursively by suffix.
        if (base < length(*front) - 1)
            radix(front, front, front + bounds[0], base + 1, bounds, static_cast<TSize>(0));
    }
    else if (back - front > 1)
        insertion_sort(front, back, base);

    // Sort next buckets on same level recursively.
    if (next == RADIX - 1) return;
    radix(top, top + parent_bounds[next], top + parent_bounds[next + 1], base, parent_bounds, next + 1);
}

template <int radix_count, typename TIter>
inline void radix_sort(TIter front, TIter back) {
    //typedef typename Container<TIter>::Type TStringSet;
    //typedef typename Value<TStringSet>::Type TString;
    //typedef typename Value<TString>::Type TChar;
    //typedef typename Size<TStringSet>::Type TSize;
    typedef typename std::iterator_traits<TIter>::value_type TString;
    typedef typename TString::value_type TChar;
    typedef typename TString::size_type TSize;

    //TSize const RADIX = ValueSize<TChar>::VALUE;
    TSize const RADIX = radix_count;
    TSize bounds[RADIX];

    radix(front, front, back, static_cast<TSize>(0), bounds, RADIX - 1);
}

} // namespace seqan


#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

const int stringcount = 100;

std::vector<std::string> get_DNA() {
    std::vector<std::string> r;
    srand((unsigned int)time(NULL));
    r.reserve(stringcount);
    char elements[] = "AGCT";
    for(int i=0; i<stringcount; ++i) {
        char data[99];
        data[98] = '\0';
        for(int i=0; i<14; ++i) {
            int v = rand();
            data[i*7+0] = elements[(v>>0)&0x3];
            data[i*7+1] = elements[(v>>2)&0x3];
            data[i*7+2] = elements[(v>>4)&0x3];
            data[i*7+3] = elements[(v>>6)&0x3];
            data[i*7+4] = elements[(v>>8)&0x3];
            data[i*7+5] = elements[(v>>10)&0x3];
            data[i*7+6] = elements[(v>>12)&0x3];
        }
        r.push_back(std::string(data, 98));
    }
    return r;
}


int main() {    
    std::vector<std::string> data = get_DNA();

    seqan::radix_sort<4>(data.begin(), data.end());

    for(auto& str : data) {
        std::cout << str << '\n';
    }
}
