#include <cstdlib>
#include <vector>
#include <iterator>
#include <iostream>

typedef std::vector <char> Packet;
typedef std::vector <Packet> Packets;

template <typename Iter> 
Iter next_upto (Iter begin, Iter end, size_t n)
{
    Iter ret = begin;
      for (; n > 0 && ret != end; ++ret, --n)
            ;   
        return ret;
}

Packets::const_iterator Process (Packets::const_iterator begin, Packets::const_iterator end)
{
  Packets::const_iterator ret = begin;
  while (ret != end)
    ++ret;  // do something
  return ret;
}

int main()
{
  const Packets test (100); // vector of 100 default-initialized packets

  // process them 10 at a time
  for (auto it = test.begin();
    it != test.end();
    it = next_upto (it, test.end(), 10))
  {
     auto itr = Process (it, next_upto (it, test.end(), 10));
     Packets::const_iterator it2 = it; 
     const size_t n1 = std::distance (it2, itr);
     const size_t n = std::distance (it, itr);
     std::cout << "Processed " << n << " packets\n";
  }
}