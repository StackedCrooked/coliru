#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

struct Information {
    Information(int n = 0) : number_(n) {}

    int number_;
    int number() const { return number_; }
};

static std::ostream& operator<<(std::ostream& os, Information const& i) {
    return os << i.number();
}

namespace bmi = boost::multi_index;

typedef boost::multi_index_container<Information, 
    bmi::indexed_by<
        bmi::hashed_non_unique<
            bmi::tag<struct idx_main>,
            bmi::const_mem_fun<Information, int, &Information::number>
        >,
        bmi::random_access<bmi::tag<struct idx_auxiliary> >
    >
> Information_Map;

struct Plus_One_Modifier {
    void operator()(Information& obj) const { obj.number_ += 1; }
};

#include <iostream>

int main() {
    Information_Map information_map_;
    std::generate_n(std::inserter(information_map_, information_map_.end()), 50, [] { return rand()%20; });

    // Updates the first element
    auto& aux = information_map_.get<idx_auxiliary>();
    auto& idx = information_map_.get<idx_main>();

    std::copy(aux.begin(), aux.end(), std::ostream_iterator<Information>(std::cout, " "));

    size_t iterations = 0;
    for(auto rait = aux.begin(); rait != aux.end(); ++rait, ++iterations) {
        auto it = bmi::project<idx_main>(information_map_, rait);
        idx.modify(it, Plus_One_Modifier());
    }

    std::cout << "\nIterations done: " << iterations << "\n";
    std::copy(aux.begin(), aux.end(), std::ostream_iterator<Information>(std::cout, " "));
}
