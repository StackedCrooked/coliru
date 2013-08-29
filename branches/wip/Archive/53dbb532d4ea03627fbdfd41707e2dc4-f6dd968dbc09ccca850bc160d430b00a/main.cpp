#include <iostream>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>

struct PriceQuote
{
    int i;
};

int main()
{
    std::vector<PriceQuote> v1{{1},{2},{3},{4}}, v2{{10},{20},{30},{40}};
    
    typedef decltype(
      boost::make_zip_iterator(
        boost::tuple<
          std::vector<PriceQuote>::iterator, 
          std::vector<PriceQuote>::iterator>()
      ) 
    ) zipper_type;
    
    zipper_type first = boost::make_zip_iterator(boost::make_tuple(v1.begin(), v2.begin()));
    zipper_type last = boost::make_zip_iterator(boost::make_tuple(v1.end(), v2.end()));

    std::for_each(first, last,
        []( boost::tuple<PriceQuote const&, PriceQuote const&> const& tup ) {
            std::cout 
              << boost::get<0>(tup).i 
              << ", " 
              << boost::get<1>(tup).i
              << std::endl;
        }
    );
}
