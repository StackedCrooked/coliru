#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

using namespace boost::multi_index;
static int idgen = 0;

enum Time_t { last_month, last_week, yesterday, today, tomorrow };
std::ostream& operator<<(std::ostream& os, Time_t tt) {
    switch(tt)
    {
        case last_month: return os << "last_month";
        case last_week:  return os << "last_week";
        case yesterday:  return os << "yesterday";
        case today:      return os << "today";
        case tomorrow:   return os << "tomorrow";
        default: return os << "?";
    };
}

struct MyData
{
    int id = ++idgen;

    MyData(Time_t timestamp) : timestamp(timestamp) {}
    Time_t timestamp;

    friend std::ostream& operator<<(std::ostream& os, MyData const& md)
    {
        return os << "(id:" << md.id << ", timestamp:" << md.timestamp << ")";
    }
};

typedef multi_index_container<
    MyData, 
        indexed_by<    
            random_access<>,  // keep insertion order
            ordered_non_unique< member<MyData, Time_t, &MyData::timestamp> >
        > 
> myContType;

typedef myContType::nth_index<1>::type myContType_by_time;

myContType myCont;

unsigned long searchByTimestamp(Time_t timestamp) 
{   
    auto& idIndex = myCont.get<0>();

    auto itTime = std::find_if(
                idIndex.rbegin(), idIndex.rend(), 
                [=](MyData const& item) { return item.timestamp == timestamp; }
            );

    if (itTime == idIndex.rend())
        return 0;

    return itTime->id; 
} 

#include <iostream>

int main()
{
    myCont.emplace_back(Time_t(last_week));
    myCont.emplace_back(Time_t(tomorrow));
    myCont.emplace_back(Time_t(last_month));
    myCont.emplace_back(Time_t(yesterday));

    std::cout << "Insertion order:\n";
    for (auto const& item : myCont)
        std::cout << item << "\n";

    std::cout << searchByTimestamp(today)     << "\n";
    std::cout << searchByTimestamp(last_month) << "\n";
}
