#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/composite_key.hpp>

struct PositionSummary {
    int                positiondate() const { return 42;  }
    std::string const& accountid()    const { return acc; }
    std::string const& instid()       const { return ins; }
  private:
    std::string acc = "a";
    std::string ins = "a";
};

namespace bmi = boost::multi_index;

typedef boost::multi_index_container<PositionSummary*,
        bmi::indexed_by<
                bmi::ordered_unique<
                        bmi::tag<struct byPosAccInst>,
                        bmi::composite_key<PositionSummary, 
                            bmi::const_mem_fun<PositionSummary, int, &PositionSummary::positiondate>,
                            bmi::const_mem_fun<PositionSummary, const std::string&, &PositionSummary::accountid>,
                            bmi::const_mem_fun<PositionSummary, const std::string&, &PositionSummary::instid> 
                        > >,
                bmi::ordered_unique<
                        bmi::tag<struct byPosInstAcc>,
                        bmi::composite_key<PositionSummary, 
                            bmi::const_mem_fun<PositionSummary, int, &PositionSummary::positiondate>,
                            bmi::const_mem_fun<PositionSummary, const std::string&, &PositionSummary::instid>,
                            bmi::const_mem_fun<PositionSummary, const std::string&, &PositionSummary::accountid> 
                        > > 
                    > > PositionSummaryContainer;

int main() 
{
    PositionSummaryContainer c;

    c.insert(new PositionSummary());

    {
        auto& index = c.get<0>();
        auto it = index.find(boost::make_tuple(42, "a", "a"));
    }
    {
        auto& index = c.get<1>();
        auto it = index.find(boost::make_tuple(42, "a", "a"));
    }

    // by tag:
    {
        auto& index = c.get<byPosAccInst>();
        auto it = index.find(boost::make_tuple(42, "a", "a"));
    }
    {
        auto& index = c.get<byPosInstAcc>();
        auto it = index.find(boost::make_tuple(42, "a", "a"));
    }
}
