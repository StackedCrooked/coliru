#include <boost/property_map/transform_value_property_map.hpp>
#include <iostream>

struct weights_t {
    float weight1, weight2, weight3, weight4;

    weights_t(float w1, float w2, float w3, float w4)
        : weight1(w1), weight2(w2), weight3(w3), weight4(w4)
    { }

    template <int which> struct access {
        typedef float result_type;

        float operator()(weights_t const& w) const { 
            BOOST_STATIC_ASSERT(which >= 1 && which <= 4);
            switch (which) {
                case 1: return w.weight1;
                case 2: return w.weight2;
                case 3: return w.weight3;
                case 4: return w.weight4;
            }
        }
    };
};

using namespace boost;

int main() {
    std::vector<weights_t> weight_data; // index is vertex id
    weight_data.push_back(weights_t(1,2,3,4));
    weight_data.push_back(weights_t(5,6,7,8));
    weight_data.push_back(weights_t(9,10,11,12));
    weight_data.push_back(weights_t(13,14,15,16));

    boost::transform_value_property_map<weights_t::access<1>, weights_t*, float> wmap1 = make_transform_value_property_map(weights_t::access<1>(), &weight_data[0]);
    boost::transform_value_property_map<weights_t::access<2>, weights_t*, float> wmap2 = make_transform_value_property_map(weights_t::access<2>(), &weight_data[0]);
    boost::transform_value_property_map<weights_t::access<3>, weights_t*, float> wmap3 = make_transform_value_property_map(weights_t::access<3>(), &weight_data[0]);
    boost::transform_value_property_map<weights_t::access<4>, weights_t*, float> wmap4 = make_transform_value_property_map(weights_t::access<4>(), &weight_data[0]);

    for (unsigned vertex = 0; vertex < weight_data.size(); ++vertex)
        std::cout << wmap1[vertex] << "\t" << wmap2[vertex] << "\t" << wmap3[vertex] << "\t"<< wmap4[vertex] << "\n";
}
