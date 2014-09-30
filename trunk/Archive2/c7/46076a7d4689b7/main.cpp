#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>


using Keys = boost::mpl::vector<double, bool, int, char, bool*>;
using Types = boost::mpl::vector<char, char, int, int, int>;

using ExpectedOutput =                                                   
    boost::mpl::vector<                                                         
        boost::mpl::pair<double, char>,                                         
        boost::mpl::pair<bool, char>,                                           
        boost::mpl::pair<int, int>,                                            
        boost::mpl::pair<char, int>,                                            
        boost::mpl::pair<bool*, int>>;

// now I perform some operation which I _think_ might work
using PairsSequence =                                                           
    typename boost::mpl::transform<                                             
        Keys,                                                            
        Types,
        boost::mpl::pair<boost::mpl::_1, boost::mpl::_2>>;

BOOST_MPL_ASSERT(( boost::mpl::equal<PairsSequence::type, ExpectedOutput> ));
