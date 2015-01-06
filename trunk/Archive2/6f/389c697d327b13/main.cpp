#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

struct Paper {
    std::string type;
    int chapter, minpage, maxpage;
};

namespace bmi = boost::multi_index;

using Papers = boost::multi_index_container<Paper,
    bmi::indexed_by<
        bmi::ordered_unique<
            bmi::tag<struct idx_key>,
            bmi::composite_key<Paper,
                bmi::member<Paper, std::string, &Paper::type>,
                bmi::member<Paper, int, &Paper::chapter>,
                bmi::member<Paper, int, &Paper::minpage>,
                bmi::member<Paper, int, &Paper::maxpage>
            >
        >,
        bmi::random_access<bmi::tag<struct idx_shuffle> >
    > >;

#include <boost/range.hpp>
#include <iostream>
#include <iomanip>
#include <set>

int main()
{
    Papers collection;
    auto& idx = collection.get<idx_key>();

    for (Paper const& p : std::vector<Paper> {
                       { "Assignation", 43, 1, 1 },
                       { "Assignation", 43, 2, 2 },
                       { "Assignation", 45, 1, 1 },
                       { "Conclusions",  9, 1, 1 },
                       { "Conclusions", 10, 1, 1 },
                       { "Conclusions", 11, 1, 1 },
                          { "Jugement", 17, 1, 1 },
                          { "Jugement", 17, 2, 2 },
                          { "Jugement", 17, 3, 3  },
                          { "Jugement", 18, 1, 1 } })
    {
        auto precedent = idx.equal_range(boost::tie(p.type, p.chapter, p.minpage));

        if (boost::empty(precedent)) {
            idx.insert(idx.end(), Paper{});
        } else { // join the chapter
            if (precedent.second->maxpage + 1 == p.minpage)
                idx.modify(precedent.second, [&p](Paper& prec) { prec.maxpage = p.maxpage; });
        }
    }

    // shuffle
    auto& ra = collection.get<idx_shuffle>();
    {
        auto gen = boost::bind(std::uniform_int_distribution<size_t>{0, ra.size()-1}, std::mt19937{});
        std::vector<boost::reference_wrapper<Paper const> > view;

        std::set<Paper const*> set4;
        Paper const*last=nullptr;

        while (set4.size() < ra.size()) {
            auto& pick = ra[gen()];
            if (set4.end() == set4.find(&pick) && (!last || last->type!=pick.type))
            {
                last = &pick;
                set4.insert(set4.end(), &pick);
                view.push_back(boost::cref(pick));
            }
        }

        ra.rearrange(view.begin());
    }

    for(auto& p : ra) 
        for(int page = p.minpage; page<=p.maxpage; ++page)
            std::cout << p.type 
                    << "-" << std::setw(3) << std::setfill('0') << p.chapter
                    << "-" << page << "-R.xml";
}
