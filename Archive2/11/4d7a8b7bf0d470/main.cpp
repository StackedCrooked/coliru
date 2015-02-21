#include <functional> // std::greater
#include <algorithm>  // std::find_if, std::sort, std::remove
#include <iostream>   // std::cout
#include <cstring>    // std::memmove
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
};

// order by priority
bool operator<(Venue const& v, unsigned int p)
{ return v.m_priority < p; }

// order by priority
bool operator<(unsigned int p, Venue const& v)
{ return v < p; }

std::array<Venue, 6> venues;
char result[7]; // 7 characters for the null character ('\0') just in case all 6 characters are non-null
int size;

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

void remove_venue(Venue* v)
{
    v->m_priority = v->m_value = 0; // venue is now empty (to be deleted)
    std::memmove(v, v + 1, (6 - size) * sizeof(Venue));
    v[5].m_value = v[5].m_priority = 0;
    --size;
}

char* AddSorted(unsigned int priority, char value)
{
    auto vit = find_venue_value(value);
    if (priority == 0) // if we want to delete
    {
        if (vit != venues.end()) // if the value is actually there, delete it
            remove_venue(&*vit);
    }
    else // otherwise
    {
        auto pit = find_venue_priority(priority);
        if (pit != venues.end()) // if we want to change the priority, and there's an existing one 
        {
            pit->m_value = value; // change the duplicate
            if (vit != venues.end()) // remove the duplicate
                remove_venue(&*vit);
        }
        else if (size < 6) // otherwise we add the venue
        {
            auto pos = std::upper_bound(venues.begin(), venues.end(), priority); // upper_bound because we are sorting from greatest to least?
            if (pos != venues.end())
            {
                std::memmove(pos + 1, pos, (6 - size) * sizeof(Venue)); // move the rest of the elements to the right
                pos->m_priority = priority; pos->m_value = value;
            }
            else
            {
                venues[size++] = Venue(priority, value); // if it's in sorted order, at add the end
            }
            ++size;
        }
        else
            return result; // return if the size is full or there is no existing element with the priority
    }
    
    // both of the above cases, if control passes here, modify venue, so we copy again
    for (int i = 0; i < venues.size(); ++i)
        result[i] = venues[i].m_value;
    return result;
}

void log(std::string const& str)
{ std::cout << str << '\n'; }

int main()
{
    // Pass
    log(AddSorted(10, 'a'));
    log(AddSorted(10, 'b'));
    log(AddSorted(10, 'c'));
    log(AddSorted(10, 'd'));
    log(AddSorted(10, 'e'));
    
    std::cout << '\n';
    
    // Pass
    log(AddSorted(0, 'a'));
    log(AddSorted(3, 'b'));
    log(AddSorted(4, 'd')); // 'd' now has highest priority
    log(AddSorted(4, 'e')); // 'e' now has 'd's priority
    log(AddSorted(0, 'b')); // delete 'b'
    log(AddSorted(0, 'e')); // delete 'e'
    
    std::cout << '\n';
    
    // Pass
    log(AddSorted(5, 'a'));
    log(AddSorted(4, 'b'));
    log(AddSorted(3, 'c'));
    log(AddSorted(2, 'd'));
    log(AddSorted(1, 'e'));
}