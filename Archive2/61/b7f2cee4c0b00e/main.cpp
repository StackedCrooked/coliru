#include <random>
#include <vector>
#include <algorithm>
#include <ostream>
#include <istream>

namespace so {
    template <typename T>
    struct uniform_sampling_distribution {
    private:
        std::vector<T> values;
        std::uniform_int_distribution<int> underlying;
    
    public:
        using result_type = T;
        using param_type = std::vector<T>;
    
        uniform_sampling_distribution() : values{0}, underlying(0, values.size()-1) {}
        template <typename Iterator>
        uniform_sampling_distribution(Iterator first, Iterator last) : values(first, last), underlying(0, values.size()-1) {}
        uniform_sampling_distribution(param_type param) : values(std::move(param)), underlying(0, values.size()-1) {}
        
        void reset() { underlying.reset(); };
    
        param_type param() const { return values; }
        void param(param_type param) {
            underlying.param(std::uniform_int_distribution<int>(0, param.size() - 1).param());
            values = std::move(param);
        }
        
        template <typename URng>
        T operator()(URng&& rng, param_type const& param) { return param[underlying(rng)]; }
    
        template <typename URng>
        T operator()(URng&& rng) { return (*this)(rng, values); }
        
        // NOTE this can be improved with some caching
        T min() const { return *std::min_element(values.begin(), values.end()); }
        T max() const { return *std::max_element(values.begin(), values.end()); }
    
        bool operator==(uniform_sampling_distribution const& that) const {
            return values.size() == that.values.size() && std::equal(values.begin(), values.end(), that.values.begin());
        }
        bool operator!=(uniform_sampling_distribution const& that) const {
            return !(*this == that);
        }
    };
    
    // TODO left as exercise for the reader
    template <typename CharT, typename CharTraits, typename T>
    std::basic_ostream<CharT, CharTraits>& operator<<(std::basic_ostream<CharT, CharTraits>& os, uniform_sampling_distribution<T> const& d);
    template <typename CharT, typename CharTraits, typename T>
    std::basic_istream<CharT, CharTraits>& operator>>(std::basic_istream<CharT, CharTraits>& is, uniform_sampling_distribution<T>& d);

}

#include <iostream>

int main() {
    so::uniform_sampling_distribution<int> d({ 17, 23, 42 });
    std::mt19937 g;
    
    for(int i = 0; i < 100; ++i) {
        std::cout << d(g) << ' ';
    }
}