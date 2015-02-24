#include "stdafx.h"

#include <functional> // std::greater
#include <algorithm>  // std::find_if, std::sort, std::remove
#include <iostream>   // std::cout
#include <cstring>    // std::memmove
#include <string>     // std::string

static const std::size_t kMaxNumberVenues = 16;

class OrderedVenues
{ 
    struct Venue_base
    {
        Venue_base(unsigned int price, unsigned int quantity)
            : price_(price)
            , quantity_(quantity)
        { }
        
        Venue_base() : price_(), quantity_() {}
      
        char id;
        unsigned int price_;
        unsigned int quantity_;
        
        // equal by priority
        bool operator==(Venue_base const& rhs) const
        { return quantity_ == rhs.quantity_; }
        
        // order by priority
        bool operator<(unsigned int q) const
        { return quantity_ < q; }
    };
public:
    typedef Venue_base Venue;
public:
    OrderedVenues() : result_(), venues_(), size_()
    {
        for (int i = 0; i < kMaxNumberVenues; ++i)
        {
            venues_[i].id = char(65 + i);
        }
    }
    void remove(Venue*);
    char* AddSorted(unsigned int, unsigned int, char);
private:
    Venue* find_venue_price(unsigned int);
    Venue* find_venue_quantity(unsigned int);
    char result_[kMaxNumberVenues + 1];
    Venue venues_[kMaxNumberVenues];
    int size_;
};

typedef OrderedVenues::Venue Venue;

Venue* OrderedVenues::find_venue_price(unsigned int value)
{
    struct local_predicate {
        local_predicate(unsigned int p) : price_(p) { }
        bool operator()(Venue const& v) { return v.price_ == price_; }
        unsigned int price_;
    } predicate(value);

    Venue* venuesEnd = venues_ + kMaxNumberVenues;
    return std::find_if(venues_, venuesEnd, predicate);
}

Venue* OrderedVenues::find_venue_quantity(unsigned int priority)
{
    struct local_predicate {
        local_predicate(unsigned int quantity) : quantity_(quantity) { }
        bool operator()(Venue const& v) { return v.quantity_ == quantity_; }
        unsigned int quantity_;
    } predicate(priority);

    Venue* venuesEnd = venues_ + kMaxNumberVenues;
    return std::find_if(venues_, venuesEnd, predicate);
}

void OrderedVenues::remove(Venue* v)
{
    std::memmove(v, v + 1, (6 - size_) * sizeof(Venue)); // move the rest of the elements to the left
    v[5].price_ = 0; // delete
    v[5].quantity_ = 0; // delete
    --size_;
}

// order by priority
bool operator<(unsigned int p, Venue const& v)
{ return v < p; }

char* OrderedVenues::AddSorted(unsigned int price, unsigned int quantity, char id)
{
    Venue* venuesEnd = venues_ + kMaxNumberVenues;
    Venue* vit = find_venue_price(price);
    if (price == 0) // if we want to delete 
    {
      if (vit != venuesEnd) // if the value is actually there, delete it
      {
        remove(vit);
      }
    }
    else // otherwise
    { 
        Venue* pit = find_venue_quantity(quantity);
        if (pit != venuesEnd) // if we want to change the priority, and there's an existing one 
        {
            pit->price_ = price; // change the duplicate
            if (vit != venues_) // remove the duplicate
            {
                remove(vit);
            }
        }
        else if (size_ < 6) // otherwise we add the venue
        {
            Venue* pos = std::upper_bound(venues_, venuesEnd, quantity); // upper_bound because we are sorting from greatest to least?
            if (pos != venuesEnd)
            {
                std::memmove(pos + 1, pos, (6 - size_) * sizeof(Venue)); // move the rest of the elements to the right
                pos->quantity_ = quantity; // insert
                pos->price_ = price; // insert
                pos->id = id;
            }
            else
            {
                venues_[size_++] = Venue(price, quantity); // if it's in sorted order, at add the end
            }
            ++size_;
        }
        else
            return result_; // return if the size is full or there is no existing element with the priority
    }
    
    // both of the above cases, if control passes here, modify venue, so we copy again
    for (int i = 0; i < kMaxNumberVenues; ++i)
    {
        result_[i] = venues_[i].price_;
    }
    return result_;
}

class NBBOTracker
{
  class BBO
  {
      int ask_quantity_;
      double ask_price_;
      int bid_quantity_;
      double bid_price_;
  };
public:
  NBBOTracker() : size() { }
  void AddBid(char, std::size_t, std::size_t);
  void AddAsk(char, std::size_t, std::size_t);
private:
  OrderedVenues bid;
  OrderedVenues ask;
  BBO bbo_array[kMaxNumberVenues];
  int size;
  BBO nbbo;
};

void NBBOTracker::AddBid(char id, std::size_t price, std::size_t qty)
{
  if (size == 0)
  {
    nbbo = Venue(id, price, qty);
  }
}

void NBBOTracker::AddAsk(char id, std::size_t price, std::size_t qty)
{
    ask.AddSorted(price, qty, id);
}

void log(std::string const& str)
{ std::cout << str << '\n'; }