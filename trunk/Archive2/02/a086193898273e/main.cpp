
#include <boost/bind.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <iomanip>
#include <iostream>
#include <map>

namespace icl = boost::icl;

template<typename T> using rw = T const*;

using Section = std::string;
using Page    = int;
using Chapter = int;
using Pages   = icl::interval_set<Page>::type;

struct Module {
    Section section;
    Chapter chapter;

    bool operator<(Module const& o) const { return boost::tie(section,chapter) < boost::tie(o.section,o.chapter); }
};

using Table = std::map<Module, Pages>;

static inline std::ostream& operator<<(std::ostream& os, Table::value_type const& p) {
    return os << p.first.section << "\t" << p.first.chapter << "\t" << p.second;
}

int main()
{
    std::cout << std::unitbuf;
    Table table;

    {
        struct Fill { Section s; Chapter c; Page p; };
        for (auto& tup : std::vector<Fill> { 
            { "Jugement",    18 , 2 },
            { "Conclusions", 11 , 1 },
            { "Assignation", 43 , 1 },
            { "Assignation", 43 , 2 },
            { "Conclusions", 10 , 1 },
            { "Jugement",    17 , 3 },
            { "Assignation", 45 , 1 },
            { "Jugement",    17 , 1 },
            { "Conclusions", 9  , 1 },
            { "Jugement",    17 , 2 },
            { "Jugement",    18 , 1 },
        })
        {
            table[{tup.s, tup.c}] += tup.p; // add page to (existing) range
        }
    }

    std::cout << "------------- table: \n";
    for (auto& r:table)
        std::cout << r << "\n";
    
    {
        using rv = Table::const_pointer;
        std::vector<rv> vw;

        for (auto& p : table)
            vw.push_back(&p);

        // blind shuffle
        srand(time(0));
        std::random_shuffle(vw.begin(), vw.end());

        // try to avoid subsequent modules from equal sections (dup)
        auto dup     = [](rv a, rv b) { return a->first.section == b->first.section; };
        auto it      = vw.begin();
        auto const e = vw.end();

        while(it != e) // bit redundant, could be while(true)
        {
            std::cout << "------------- STATE: \n";
            for (auto& rv:vw)
                std::cout << *rv << (*it == rv? "*\n":"\n");

            it = std::adjacent_find(it, e, dup);
            if (it == e) 
                break;
            
            std::cout << "------------- dupes: \n";
            std::cout << "\t" << **(it+0) << "\n";
            std::cout << "\t" << **(it+1) << "\n";

            auto m = std::find_if(it+1, e, [&] (rv r) { return r->first.section != (*it)->first.section; });

            if (m == e)
            {
                it = m;
            } else
            {
                std::cout << "------------- rotating to: \n";
                std::cout << "\t" << *m << "\n";

                std::rotate(it+1, m, e);

                it = std::adjacent_find(it, e, dup);
            }
        }
        std::cout << "------------- selection: \n";
        for (auto& r : vw)
            std::cout << *r << "\n";
    }
}
