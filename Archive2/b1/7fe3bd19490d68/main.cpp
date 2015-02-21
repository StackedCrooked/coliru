#include <functional> // std::greater
#include <algorithm>  // std::find_if, std::sort, std::remove
#include <iostream>   // std::cout
#include <string>     // std::string
#include <array>      // std::array

struct Venue
{
    Venue(unsigned int priority = 0, char value = 0)
        : m_priority(priority)
        , m_value(value)
    { }
    
    unsigned int m_priority;
    char m_value;
    
    // equal by priority
    bool operator==(Venue const& rhs) const
    { return m_priority == rhs.m_priority; }
    
    // order by priority
    bool operator>(Venue const& rhs) const
    { return m_priority > rhs.m_priority; }
};

std::array<Venue, 6> venues;
char result[7]; // 7 characters for the null character ('\0') just in case all 6 characters are non-null
int pos;

Venue* find_venue_value(char value)
{
    return std::find_if(venues.begin(), venues.end(),
        [&] (Venue const& v) { return v.m_value == value; });
}

Venue* find_venue_priority(unsigned int priority)
{
    return std::find_if(venues.begin(), venues.end(),
        [&] (Venue const& v) { return v.m_priority == priority; });
}

void remove_venue(Venue& v)
{
    v.m_priority = v.m_value = 0; // venue is now empty (to be deleted)
    std::remove(venues.begin(), venues.end(), v); // moves venue element to the end of the array (doesn't actually delete it)
    --pos;
}

char* AddSorted(unsigned int priority, char value)
{
    auto vit = find_venue_value(value);
    if (priority == 0)
    {
        if (vit != venues.end())
            remove_venue(*vit);
    }
    else
    {
        auto pit = find_venue_priority(priority);
        if (pit != venues.end())
        {
            pit->m_value = value;
            if (vit != venues.end())
                remove_venue(*vit);
        }
        else if (pos < 6)
            venues[pos++] = Venue(priority, value);
        else
            return result;
    }
    // sort from greatest priority to least
    std::sort(venues.begin(), venues.end(), std::greater<Venue>());
    
    for (int i = 0; i < venues.size(); ++i)
        result[i] = venues[i].m_value;
    return result;
}

void log(std::string const& str)
{ std::cout << str << '\n'; }

int main()
{
    log(AddSorted(10, 'a'));
    log(AddSorted(10, 'b'));
    log(AddSorted(10, 'c'));
    log(AddSorted(10, 'd'));
    log(AddSorted(10, 'e'));
    
    std::cout << '\n';
    
    log(AddSorted(0, 'a')); // delete 'a'
    log(AddSorted(3, 'b')); // change 'b's priority to 'c's
    log(AddSorted(4, 'd')); // 'd' now has highest priority
    log(AddSorted(4, 'e')); // 'e' now has 'd's priority
    log(AddSorted(0, 'b')); // delete 'b'
    log(AddSorted(0, 'e'));
    
    std::cout << '\n';
    
    log(AddSorted(5, 'a'));
    log(AddSorted(4, 'b'));
    log(AddSorted(3, 'c'));
    log(AddSorted(2, 'd'));
    log(AddSorted(1, 'e'));
}