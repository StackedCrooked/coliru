#include "stdafx.h"

#include <functional> // std::greater
#include <algorithm>  // std::find_if, std::sort, std::remove
#include <iostream>   // std::cout
#include <cstring>    // std::memmove
#include <string>     // std::string
#include <cstdint>    // std::int8_t
/*

A list of Venues reverse sorted by quantity. All venues have the same price. It doens't matter if it's an ask or a bid

*/

static const std::size_t kMaxNumberVenues = 16;

class OrderedVenues {
public:
    struct Venue {
        int8_t id;
        unsigned int quantity;
    };

    OrderedVenues()
      : result_(),
        venues_(),
        size_()
    {
    }

    int8_t* AddSorted(unsigned int quantity, int8_t id);
    Venue* FindVenueId(int8_t id);
    Venue* FindVenueQuantity(unsigned int quantity);
    void clear();
private:
    void Remove(Venue* v);
    void RemoveAll(int8_t id);
    void Insert(unsigned int quantity, int8_t id);

    int8_t result_[kMaxNumberVenues + 1];
    Venue venues_[kMaxNumberVenues];
    size_t size_;
};

void OrderedVenues::clear()
{
  std::memset(venues_, 0, sizeof venues_);
}

OrderedVenues::Venue* OrderedVenues::FindVenueId(int8_t id) {
  for (size_t i = 0; i < size_; ++i)
  {
    if (venues_[i].id == id)
    {
      return &venues_[i];
    }
  }
  return NULL;
}

OrderedVenues::Venue* OrderedVenues::FindVenueQuantity(unsigned int quantity)
{
  Venue* pos = std::lower_bound(venues_, venues_ + size_, quantity);
  if (pos != venues_ + size_)
  {
    return pos;
  }
  return NULL;
}

// order by quantity
bool operator<(OrderedVenues::Venue const& v, unsigned int quantity)
{ return v.quantity < quantity; }
// order by quantity
bool operator<(unsigned int quantity, OrderedVenues::Venue const& v)
{ return quantity < v.quantity; }

void OrderedVenues::Remove(Venue* v)
{
  std::memmove(v, v + 1, (kMaxNumberVenues - size_) * sizeof(Venue));
  venues_[kMaxNumberVenues - 1].id = 0;
  venues_[kMaxNumberVenues - 1].quantity = 0;
  --size_;
}

void OrderedVenues::RemoveAll(int8_t id)
{
  for (Venue* vit = FindVenueId(id); vit != NULL; vit = FindVenueId(id))
  {
    Remove(vit);
  }
}

void OrderedVenues::Insert(unsigned int quantity, int8_t id)
{
    Venue* venuesEnd = venues_ + size_;
    // find the value in the sorted array
    
    Venue* pos = venuesEnd;
    for (size_t i = 0; i < size_; ++i)
    {
      if (quantity >= venues_[i].quantity)
      {
        pos = &venues_[i];
        break;
      }
    }

    if (pos != venuesEnd) // if there's no value lesser, then insert at front
    {
      if (size_ != 0) // if there are no elements then there's no point in copying
      {
        std::memmove(pos + 1, pos, (kMaxNumberVenues - size_ - 1) * sizeof(Venue)); // move the rest of the elements to the right
      }
      pos->quantity = quantity; // insert
      pos->id = id; // insert
    }
    else
    {
        Venue temp;
        temp.id = id;
        temp.quantity = quantity;
        venues_[size_] = temp; // if it's the smallest found, insert at end
    }
    ++size_;
}

int8_t* OrderedVenues::AddSorted(unsigned int quantity, int8_t id)
{
  Venue* vit = FindVenueId(id);
  if (quantity == 0) // if we want to delete
  {
    if (vit != NULL)
    {
      Remove(vit);
    }
  }
  else // otherwise
  {
      if (vit != NULL) // if the element is found and we don't want to delete it, then we're changing its quantity
      {
        int count = 1; // how many elements to insert
        for (; vit != NULL; vit = FindVenueId(id)) { // keep finding venues with their id equal to the parameter id
          Remove(vit); // remove them so we can add them in sorted order later
          ++count;
        }

        while (count--)
        {
          Insert(quantity, id); // insert sorted
        }
      }
      else if (size_ < kMaxNumberVenues) // if we want to change the priority
      {
        Insert(quantity, id);
      }
      else
      {
        return result_; // return if the array is full
      }
  }

  // both of the above cases, if control passes here, modify venue, so we copy again
  for (size_t i = 0; i < size_; ++i)
  {
      result_[i] = venues_[i].id;
  }

  std::memset(result_ + size_, 0, kMaxNumberVenues - size_);
  return result_;
}

class NBBOTracker
{
public:
  typedef OrderedVenues::Venue Venue;

  struct BBO
  {
      int ask_quantity_;
      double ask_price_;
      int bid_quantity_;
      double bid_price_;

      BBO() : ask_quantity_(), ask_price_(), bid_quantity_(), bid_price_() { }
  };

  NBBOTracker() : bid_order(), ask_order(), bbo_array(), size(), nbbo() { }
  void AddBid(int8_t, std::size_t, std::size_t);
  void AddAsk(int8_t, std::size_t, std::size_t);

  BBO NBBO() const;
private:
  OrderedVenues bid_order;
  OrderedVenues ask_order;
  BBO  bbo_array[kMaxNumberVenues];

  size_t size;
  BBO nbbo;
};

// Find the highest bid, lowest offer. Sum the quantities of those venues.
// The NNBO is single object that contains the highest big and lowest offer in the BBO array
// bid_order is for ordering the venues, ask_order is for ordering the asks

void NBBOTracker::AddBid(int8_t id, std::size_t price, std::size_t qty)
{
  std::size_t xid = id % 16; // The id (character) converted back to an integer
  if (price == nbbo.bid_price_)
  {
    if (bbo_array[xid].bid_price_ == nbbo.bid_price_)
    {
      nbbo.bid_quantity_ -= bbo_array[xid].bid_quantity_;
    }
    nbbo.bid_quantity_ += qty;
    bid_order.AddSorted(id, qty);
  }
  else if (price < nbbo.bid_price_)
  {
    if (bbo_array[xid].bid_price_ == nbbo.bid_price_) {
      nbbo.bid_quantity_ -= qty;
    }
    if (nbbo.bid_quantity_ == 0) {
      // recalculate (for loop find max price & sum the qty)
      
      // Finding the maximum price
      BBO max = bbo_array[0];
      for (size_t i = 1; i < size; ++i)
      {
        if (bbo_array[i].bid_price_ < max.bid_price_)
        {
          max = bbo_array[i];
        }
      }

      // Summing up the quantities of the bbos with the same quantity as the venue with the highest price
      for (size_t i = 0; i < size; ++i)
      {
        if (bbo_array[i].bid_quantity_ == max.bid_quantity_)
        {
          nbbo.bid_quantity_ += bbo_array[i].bid_quantity_;
        }
      }
    }
    else if (price > nbbo.bid_price_)
    {
      nbbo.bid_price_ = price;
      nbbo.bid_quantity_ = qty;
      bid_order.clear();
      bid_order.AddSorted(id, qty);
    }
    bbo_array[xid].bid_quantity_ = qty;
    bbo_array[xid].bid_price_ = price;
  }

}

void NBBOTracker::AddAsk(int8_t id, std::size_t price, std::size_t qty)
{
  std::size_t xid = id % 16; // convert it to work with indicies
  if (price == nbbo.ask_price_)
  {
    if (bbo_array[xid].ask_price_ == nbbo.ask_price_)
    {
      nbbo.ask_quantity_ -= bbo_array[xid].ask_quantity_;
    }
    nbbo.ask_quantity_ += qty;
    ask_order.AddSorted(id, qty);
  }
  else if (price < bbo_array[xid].ask_price_)
  {
    if (bbo_array[xid].ask_price_ == nbbo.ask_price_)
    {
      nbbo.ask_quantity_ -= qty;
    }

    if (nbbo.ask_quantity_ == 0)
    {
      // Recaculate: For loop to find the maximum price, then sum up the quantities of the venues
    }
  }
  else if (price > nbbo.ask_price_)
  {
    nbbo.ask_price_ = price;
    nbbo.ask_quantity_ = qty;
    ask_order.clear();
    ask_order.AddSorted(id, qty);
  }
  bbo_array[xid].bid_quantity_ = qty;
  bbo_array[xid].bid_price_ = price;
}

NBBOTracker::BBO NBBOTracker::NBBO() const
{
    return nbbo;
}

void log(std::string const& str)
{ std::cout << str << '\n'; }


//#include "stdafx.h"
//
//#include <functional> // std::greater
//#include <algorithm>  // std::find_if, std::sort, std::remove
//#include <iostream>   // std::cout
//#include <cstring>    // std::memmove
//#include <string>     // std::string
//
///*
//
//A list of Venues reverse sorted by quantity. All venues have the same price. It doens't matter if it's an ask or a bid
//
//*/
//
//static const std::size_t kMaxNumberVenues = 16;
//
//class OrderedVenues
//{
//    struct Venue_base
//    {
//        Venue_base(unsigned int price, unsigned int quantity)
//            : price_(price)
//            , quantity_(quantity)
//        { }
//
//        Venue_base() : price_(), quantity_() {}
//
//        int8_t id;
//        unsigned int price_;
//        unsigned int quantity_;
//
//        // equal by priority
//        bool operator==(Venue_base const& rhs) const
//        { return quantity_ == rhs.quantity_; }
//
//        // order by priority
//        bool operator<(unsigned int q) const
//        { return quantity_ < q; }
//    };
//public:
//    typedef Venue_base Venue;
//public:
//    OrderedVenues() : result_(), venues_(), size_()
//    {
//        for (int i = 0; i < kMaxNumberVenues; ++i)
//        {
//            venues_[i].id = int8_t(65 + i);
//        }
//    }
//    void remove(Venue*);
//    int8_t* AddSorted(unsigned int, unsigned int, int8_t);
//private:
//    Venue* find_venue_price(unsigned int);
//    Venue* find_venue_quantity(unsigned int);
//    int8_t result_[kMaxNumberVenues + 1];
//    Venue venues_[kMaxNumberVenues];
//    int size_;
//};
//
//typedef OrderedVenues::Venue Venue;
//
//Venue* OrderedVenues::find_venue_price(unsigned int value)
//{
//    struct local_predicate {
//        local_predicate(unsigned int p) : price_(p) { }
//        bool operator()(Venue const& v) { return v.price_ == price_; }
//        unsigned int price_;
//    } predicate(value);
//
//    Venue* venuesEnd = venues_ + kMaxNumberVenues;
//    return std::find_if(venues_, venuesEnd, predicate);
//}
//
//Venue* OrderedVenues::find_venue_quantity(unsigned int priority)
//{
//    struct local_predicate {
//        local_predicate(unsigned int quantity) : quantity_(quantity) { }
//        bool operator()(Venue const& v) { return v.quantity_ == quantity_; }
//        unsigned int quantity_;
//    } predicate(priority);
//
//    Venue* venuesEnd = venues_ + kMaxNumberVenues;
//    return std::find_if(venues_, venuesEnd, predicate);
//}
//
//void OrderedVenues::remove(Venue* v)
//{
//    std::memmove(v, v + 1, (6 - size_) * sizeof(Venue)); // move the rest of the elements to the left
//    v[5].price_ = 0; // delete
//    v[5].quantity_ = 0; // delete
//    --size_;
//}
//
//// order by priority
//bool operator<(unsigned int p, Venue const& v)
//{ return v < p; }
//
//int8_t* OrderedVenues::AddSorted(unsigned int price, unsigned int quantity, int8_t id)
//{
//    Venue* venuesEnd = venues_ + kMaxNumberVenues;
//    Venue* vit = find_venue_price(price);
//    if (price == 0) // if we want to delete
//    {
//      if (vit != venuesEnd) // if the value is actually there, delete it
//      {
//        remove(vit);
//      }
//    }
//    else // otherwise
//    {
//        Venue* pit = find_venue_quantity(quantity);
//        if (pit != venuesEnd) // if we want to change the priority, and there's an existing one
//        {
//            pit->price_ = price; // change the duplicate
//            if (vit != venues_) // remove the duplicate
//            {
//                remove(vit);
//            }
//        }
//        else if (size_ < 6) // otherwise we add the venue
//        {
//            Venue* pos = std::upper_bound(venues_, venuesEnd, quantity); // upper_bound because we are sorting from greatest to least?
//            if (pos != venuesEnd)
//            {
//                std::memmove(pos + 1, pos, (6 - size_) * sizeof(Venue)); // move the rest of the elements to the right
//                pos->quantity_ = quantity; // insert
//                pos->price_ = price; // insert
//                pos->id = id;
//            }
//            else
//            {
//                venues_[size_++] = Venue(price, quantity); // if it's in sorted order, at add the end
//            }
//            ++size_;
//        }
//        else
//            return result_; // return if the size is full or there is no existing element with the priority
//    }
//
//    // both of the above cases, if control passes here, modify venue, so we copy again
//    for (int i = 0; i < kMaxNumberVenues; ++i)
//    {
//        result_[i] = venues_[i].price_;
//    }
//    return result_;
//}
//
//class NBBOTracker
//{
//  struct BBO
//  {
//      int ask_quantity_;
//      double ask_price_;
//      int bid_quantity_;
//      double bid_price_;
//
//      BBO() : ask_quantity_(), ask_price_(), bid_quantity_(), bid_price_() { }
//  };
//public:
//  NBBOTracker() : size() { }
//  void AddBid(int8_t, std::size_t, std::size_t);
//  void AddAsk(int8_t, std::size_t, std::size_t);
//
//  Venue* nbbo() const;
//private:
//  OrderedVenues bid;
//  OrderedVenues ask;
//  BBO bbo_array[kMaxNumberVenues];
//  int size;
//  BBO nbbo;
//};
//
//void NBBOTracker::AddBid(int8_t id, std::size_t price, std::size_t qty)
//{
//  bid.AddSorted(price, qty, id);
//}
//
//void NBBOTracker::AddAsk(int8_t id, std::size_t price, std::size_t qty)
//{
//  ask.AddSorted(price, qty, id);
//}
//
//Venue* NBBOTracker::nbbo() const
//{
//    return nbbo;
//}
//
//void log(std::string const& str)
//{ std::cout << str << '\n'; }