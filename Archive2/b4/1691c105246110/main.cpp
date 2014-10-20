#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using MainKey      = int;
using SecondaryKey = int;
using Data         = std::string;

struct RecordKey
{
    MainKey         mainKey;
    SecondaryKey    secondaryKey;

    RecordKey( const MainKey mainKey, SecondaryKey secondaryKey):
        mainKey( mainKey),
        secondaryKey( secondaryKey)
    {}
};

struct Record: public RecordKey
{
    Data data;

    Record( const MainKey mainKey = 0, const SecondaryKey secondaryKey = 0, const Data& data = 0):
        RecordKey( mainKey, secondaryKey),
        data( data)
    {}

    friend std::ostream& operator<<(std::ostream& os, Record const& r) {
        return os << " Record[" << r.mainKey << ", " << r.secondaryKey << ", " << r.data << "]";
    }
};

struct MainKeyTag {};
struct SecondaryKeyTag {};
struct CompositeKeyTag {};

using boost::multi_index_container;
using namespace boost::multi_index;

typedef boost::multi_index_container<
    Record,
    indexed_by<
        ordered_non_unique< tag<CompositeKeyTag>, 
        composite_key<Record, 
                    member<RecordKey, MainKey, &RecordKey::mainKey>,
                    member<RecordKey, SecondaryKey, &RecordKey::secondaryKey>
    > > > > RecordContainer;
                                                        

int main()
{
    RecordContainer records;
    records.insert(Record(1, 2, "12"));
    records.insert(Record(1, 3, "13"));
    records.insert(Record(1, 3, "13 - need not be unique!"));
    records.insert(Record(3, 4, "34"));
    records.insert(Record(3, 5, "35"));
    records.insert(Record(5, 6, "56"));
    records.insert(Record(5, 7, "57"));
    records.insert(Record(7, 8, "78"));

    std::cout << "\nAll records:\n----------------------------------------------------------------------\n";
    for (auto const& r : records)
        std::cout << r << "\n";

    {
        std::cout << "\nAll records with (main) == (1):\n----------------------------------------------------------------------\n";
        auto& index = records.get<0>();
        auto range = index.equal_range(1);
        for (auto const& r : boost::make_iterator_range(range.first, range.second))
            std::cout << r << "\n";
    }

    {
        std::cout << "\nAll records with (main,secondary) == (1,3):\n----------------------------------------------------------------------\n";
        auto& index = records.get<0>();
        auto range = index.equal_range(boost::make_tuple(1,3));
        for (auto const& r : boost::make_iterator_range(range.first, range.second))
            std::cout << r << "\n";
    }
}
