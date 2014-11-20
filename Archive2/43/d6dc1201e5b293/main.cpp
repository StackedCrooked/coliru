#include <boost/uuid/uuid.hpp>            
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp> 
#include <iostream>

using namespace std;
using namespace boost;
using namespace uuids;

std::vector<uuid> foo() {
    std::vector<uuid> r;
    std::generate_n(back_inserter(r), 40, random_generator());
    return r;
}


int main() {
    for(auto& uuid : foo())
        cout << uuid << endl;
}
