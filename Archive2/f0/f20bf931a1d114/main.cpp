#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/random.hpp>
#include <boost/bind.hpp>

using namespace boost::accumulators;

static const size_t MAX_CACHE_ENTRIES = 32;

template <typename Tag=int>
class Histogram {
    public:
        Histogram(int bins, size_t cache)
            : acc(accumulator_set<double,
                    features<tag::min, tag::max, tag::mean, tag::density>>(
                        tag::density::num_bins = bins,
                        tag::density::cache_size = std::min(cache, MAX_CACHE_ENTRIES))) {
            }        
        
        accumulator_set<double,
                        features<tag::min, tag::max, tag::mean, tag::density>> acc;
};

int main()
{
    Histogram<> position_histogram { 10, 32 };
    Histogram<> action_histogram   { 10, 32 };

    auto random = boost::bind(boost::uniform_real<double>(-100,100), boost::mt19937(42));

    size_t samples = 1<<20;
    while (samples--)
    {
        auto v = random();
        position_histogram.acc(v);
        action_histogram.acc(v);
    }

    for (auto& acc : { position_histogram.acc, action_histogram.acc })
    {
        auto hist = density(acc);

        double total = 0.0;

        for( int i = 0; i < hist.size(); i++ ) 
        {
            std::cout << "Bin lower bound: " << hist[i].first << ", Value: " << hist[i].second << std::endl; 
            total += hist[i].second;
        }

        std::cout << "Total: " << total << std::endl; //should be 1 (and it is)
    }
}
