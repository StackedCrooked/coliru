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

    std::function<bool(MyData const&)> criteria = 
        [=](MyData const& item) { return item.timestamp >= timestamp; };

    auto current = idIndex.rbegin();
    while(current != idIndex.rend())
    {
        current = std::find_if(current, idIndex.rend(), criteria);

        if (current != idIndex.rend())
        {
            bool some_extra_condition = current->timestamp == timestamp; // exact match?

            if (some_extra_condition)
                return current->id; // we have an exact match
        } else
        {
            // otherwise look for the next item that has an id divisible by 3 (3,6,9,...)
            criteria = [](MyData const& item) { return (item.id % 3) == 0; };
        }
    }

    if (current == idIndex.rend())
        return 0;

    return current->id; 
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
