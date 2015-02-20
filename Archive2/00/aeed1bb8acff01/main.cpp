#include <algorithm>
#include <iostream>
#include <array>

struct Venue
{
    Venue(unsigned int priority = 0, char value = 0)
        : m_priority(priority)
        , m_value(value)
    { }
    unsigned int m_priority;
    char m_value;
};

// equal by priority
bool operator==(Venue const& lhs, Venue const& rhs)
{ return lhs.m_priority == rhs.m_priority; }

// order by priority
bool operator>(Venue const& lhs, Venue const& rhs)
{ return lhs.m_priority > rhs.m_priority; }

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
}

char* AddSorted(unsigned int priority, char value)
{
    auto vit = find_venue_value(value);
    if (vit != venues.end()) // if we found the element then we are either changing its priority or deleting it:
    {
        auto pit = find_venue_priority(priority);
        if (priority == 0)
            remove_venue(*vit);
            
        else if (pit != venues.end()) // if we find an element with the same priority,
        {                             
            pit->m_value = value; // then change the element's m_value to value and
            remove_venue(*vit);   // delete old element
        }
        else // if priority != 0 and there was no duplicate, then just change the priority
            vit->m_priority = priority;
    }
    else if (pos < 6) // if the venue was not found, we are adding a new one
        venues[pos++] = Venue(priority, value);
    else
        return result; // if the element was not found and the array is full, then there is nothing to do
        
    // sort from greatest priority to least
    std::sort(venues.begin(), venues.end(), std::greater<Venue>());
    
    for (int i = 0; i < 6; ++i)
    {
        result[i] = venues[i].m_value;
    }
    return result;
}

void log(std::string const& str)
{ std::cout << str << '\n'; }

int main()
{
    log(AddSorted(5, 'a'));
    log(AddSorted(4, 'b'));
    log(AddSorted(3, 'c'));
    log(AddSorted(2, 'd'));
    log(AddSorted(1, 'e'));
    
    std::cout << '\n';
    
    log(AddSorted(0, 'a')); // delete 'a'
    log(AddSorted(3, 'b')); // change 'b's priority to 'c's
    log(AddSorted(4, 'd')); // 'd' now has highest priority
    log(AddSorted(4, 'e')); // 'e' now has 'd's priority
    log(AddSorted(0, 'b')); // delete 'b'
}