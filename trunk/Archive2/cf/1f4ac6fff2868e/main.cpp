#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <fstream>

class RawData {
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, unsigned) { ar &data; }

  public:
    std::vector<double> data;
    static void save(RawData rd, std::string path) {
        std::ofstream file(path);
        boost::archive::binary_oarchive oa(file, std::ios_base::binary);
        oa << rd;
    }

    static void load(RawData &rd, std::string path) {
        std::ifstream file(path);

        boost::archive::binary_iarchive ia(file, std::ios_base::binary);
        ia >> rd;
        file.close();
    }
};

#include <iostream>

RawData generate() { 
    RawData old_data;

    for (int i = 0; i < 10000; i++)
        old_data.data.push_back((double)i);

    return old_data;
}

int main() {
    RawData const old_data = generate();

    RawData::save(old_data, "test.data");

    // deserialize
    RawData new_data;
    RawData::load(new_data, "test.data");

    assert(old_data.data == new_data.data);
}

