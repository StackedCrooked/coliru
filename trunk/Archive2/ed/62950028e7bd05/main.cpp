#include <boost/mpl/vector.hpp>
using namespace boost;
#include <boost/gil/gil_all.hpp>
using namespace boost::gil;

#include <boost/algorithm/searching/boyer_moore.hpp>
using namespace boost::algorithm;

namespace boost { namespace gil
{
    template <typename ChannelValue, typename Layout>
    std::size_t hash_value(pixel<ChannelValue,Layout> const& b)
    {
        std::size_t seed=0;
        for (int c=0; c<num_channels<pixel<ChannelValue,Layout> >::value; ++c)
            hash_combine(seed,b[c]);
        return seed;
    }
}}

int main() {
    typedef rgba8_image_t image_t;
    typedef image_t::view_t view_t;

    view_t vw;

    boyer_moore<view_t::x_iterator> bm(vw.row_begin(0), vw.row_end(0)); // compile error
}