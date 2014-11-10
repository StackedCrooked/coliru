#include <boost/property_map/property_map.hpp>
#include <boost/property_map/function_property_map.hpp>

using namespace boost;

struct SpecificMessage {
    // add some data
    int index; // just for demo
};

template <typename Message>
struct MyLazyReader {
    typedef Message type;
    std::string fname;

    MyLazyReader(std::string fname) : fname(fname) {}

    Message operator()(size_t index) const { 
        Message m;
        // FileReader fr;
        // fr.open(fname);
        // fr.moveTo(index);     // Move to Message 
        // fr.read(&m);          // Try deserializing as SpecificMessage  
        m.index = index; // just for demo
        return m;
    }
};

#include <iostream>

int main() {

    auto lazy_access = make_function_property_map<size_t>(MyLazyReader<SpecificMessage>("file.bin"));

    for (int i=0; i<10; ++i)
        std::cout << lazy_access[rand()%256].index << "\n";
}
