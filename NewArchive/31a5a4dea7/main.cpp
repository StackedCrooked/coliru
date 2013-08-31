/* 
    Compile with cl /EHsc /IY:\boost\ present.cpp from the Visual Studio Command Prompt
    alternatively g++ -std=c++11 main.cpp && ./a.out or clang++ -std=c++11 -O2 -pthread main.cpp && ./a.out within coliru
*/

// see http://www.boost.org/doc/libs/1_54_0/libs/utility/utility.htm for why this should be defined in VS2010
#define BOOST_RESULT_OF_USE_TR1_WITH_DECLTYPE_FALLBACK 

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/range/adaptors.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

// Just some generic class
class Thing
{
public:
  Thing() : _id(0), _name(std::string("")){}
  Thing(const Thing& t) : _id(t._id), _name(t._name){}
  void operator=(const Thing& t){_id = t._id; _name = t._name;}
  std::size_t _id;
  std::string _name;
private:
};

int main() {
  // Just some generic container
  Thing thingy;
  std::vector<Thing> thingys;
  thingys.push_back(thingy);
  thingy._name = std::string("blank");
  thingys.push_back(thingy);

  // Let's sort by id using a functor
  struct Functor
  {
    Functor(){}
    bool operator()(const Thing& lhs, const Thing& rhs){ return lhs._id > rhs._id;}
  };
  Functor funct;

  // pass it into the sort function
  std::sort(thingys.begin(), thingys.end(), funct);

  // This is all a bit verbose, so let's try sorting by name with a lambda
  std::sort(thingys.begin(), thingys.end(), [](const Thing& lhs, const Thing& rhs){return lhs._name > rhs._name;});

  // Much better, now, let's try doing the equivalent of a 'Filter' operation
  std::vector<Thing> filtered;
  std::string filterName = "blank";
  std::copy_if(thingys.begin(), thingys.end(), std::back_inserter(filtered), [=](const Thing& thingy){return thingy._name == filterName;});
  // notice the = sign, this specifies that all auto variables currently in scope are captured by value

  // Equivalent to a 'Map' operation
  std::vector<Thing> mapped;
  std::size_t mappedCount = 0;
  std::transform(filtered.begin(), filtered.end(), std::back_inserter(mapped),
      [&](const Thing& thingy) -> const Thing
      {
        Thing thingy2(thingy);
        mappedCount++;
        thingy2._name += " mapped";
        return thingy2;
      }
    );
  // this time the & sign means we are capturing everything by reference
  // also the -> allows us to specify a return type if the closure is longer than one return statement

  // std::vector<int> vec = {1, 2, 3, 5, 5}; No initialiser list in VS2010!
  std::vector<int> vec;
  for (int i=0;i<6;i++)
    vec.push_back(1);

  boost::copy( vec | boost::adaptors::reversed
                   | boost::adaptors::uniqued
                   | boost::adaptors::filtered([](int i){return i>=0;}),
               std::ostream_iterator<int>(std::cout) );

  std::vector<Thing> piped;
  // note that lambdas have deleted copy assignment operators
  // so we *must* use a move constructor here
  std::function<Thing (Thing)> transform( [](Thing t)->Thing{
    t._name = "wiped";
    return t;});

  boost::copy(thingys
      | boost::adaptors::filtered([](const Thing& t){return t._id < 1;})
      | boost::adaptors::transformed(transform)
      | boost::adaptors::reversed,
      std::back_inserter(piped)
      );
  // alternatively
  std::function<bool (const Thing& t)> filter([](const Thing& t){return t._id > 0;});

  std::cref(filter);
  // create a reference so that move semantics can be used.
  boost::push_back(piped, thingys
      | boost::adaptors::filtered(filter)
      | boost::adaptors::filtered([](const Thing& t){return t._id > 0;})
      );
}
