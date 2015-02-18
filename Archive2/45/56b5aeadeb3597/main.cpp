#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>

struct DataChunk {
  public:
    double data[2048]; // THIS IS THE PROBLEM AREA
    int end;

  private:
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, unsigned) {
        ar & end;
        ar & boost::serialization::make_array(data, end);
    }
};

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>

class RawData {
  private:
    std::vector<DataChunk> chunks;
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, unsigned) { ar &chunks; }

  public:
    void add_chunk(DataChunk chunk) { chunks.push_back(chunk); };
    std::vector<DataChunk> get_chunks() { return chunks; };
    static void save(RawData rd, std::string path);
    static bool load(RawData &rd, std::string path);

    void add_raw_data(std::vector<double> raw_data) {
        DataChunk chunk;
        auto const csize = boost::size(chunk.data);

        size_t n    = raw_data.size(), 
               offs = 0ul;

        while (n>0) {
            auto n_ = std::min(n, csize);
            std::copy_n(raw_data.begin() + offs, n_, chunk.data);
            chunk.end = n_;
            chunks.push_back(chunk);
            offs += n_;
            n    -= n_;
        }
    }

    std::vector<double> combine_chunks() {
        std::vector<double> r;
        boost::for_each(chunks, [&r](DataChunk const& c) {std::copy_n(c.data, c.end, back_inserter(r));});
        return r;
    }
};

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <fstream>

void RawData::save(RawData rd, std::string path) {
    std::ofstream file(path);
    if (file.good()) {

        boost::archive::binary_oarchive oa(file, std::ios::binary);
        // boost::archive::text_oarchive oa(file);
        oa << rd;
    }
    file.flush();
    file.close();
}

bool RawData::load(RawData &rd, std::string path) {
    std::ifstream file(path);
    if (file.good()) {

        boost::archive::binary_iarchive ia(file, std::ios::binary);
        // boost::archive::text_iarchive ia(file);
        ia >> rd;
        file.close();
        return true;
    } else
        return false;
}

#include <iostream>

RawData generate() {
    RawData data;
    std::vector<double> raw_data;
    for (int i = 0; i < 5000; i++)
        raw_data.push_back(i * 2048);
    data.add_raw_data(raw_data);
    return data;
}

int main() {
    std::string const path = "test.data";

    {
        // serialize
        RawData const old_data = generate();
        RawData::save(old_data, path);
    }

    {
        // deserialize
        RawData new_data;
        RawData::load(new_data, path);

        // grab the chunks and test the values
        for (auto d : new_data.combine_chunks())
            std::cout << d << ", ";
    }
}
