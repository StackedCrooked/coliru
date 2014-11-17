#include <boost/property_map/function_property_map.hpp>
#include <iostream>

struct weights_t {
    float weight1, weight2, weight3, weight4;
};

using namespace boost;

int main() {
    std::vector<weights_t> weight_data { // index is vertex id
        { 1,2,3,4 },
        { 5,6,7,8 },
        { 9,10,11,12 },
        { 13,14,15,16 }, 
    };

    auto wmap1 = make_function_property_map<unsigned, float>([&weight_data](unsigned vertex_id) { return weight_data.at(vertex_id).weight1; });
    auto wmap2 = make_function_property_map<unsigned, float>([&weight_data](unsigned vertex_id) { return weight_data.at(vertex_id).weight2; });
    auto wmap3 = make_function_property_map<unsigned, float>([&weight_data](unsigned vertex_id) { return weight_data.at(vertex_id).weight3; });
    auto wmap4 = make_function_property_map<unsigned, float>([&weight_data](unsigned vertex_id) { return weight_data.at(vertex_id).weight4; });

    for (unsigned vertex = 0; vertex < weight_data.size(); ++vertex)
        std::cout << wmap1[vertex] << "\t" << wmap2[vertex] << "\t" << wmap3[vertex] << "\t"<< wmap4[vertex] << "\n";
}
