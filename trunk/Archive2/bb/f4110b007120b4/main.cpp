#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/container/scoped_allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <iostream>

namespace bip = boost::interprocess;
using blob_t       = bip::vector<uint8_t, bip::allocator<uint8_t, bip::managed_mapped_file::segment_manager> >;
#if 1
using shared_blobs = bip::vector<blob_t,  bip::allocator<blob_t,  bip::managed_mapped_file::segment_manager> >;
#else
using alloc        = boost::container::scoped_allocator_adaptor<shared_blobs::allocator_type, blob_t::allocator_type>;
#endif

struct SpecificMessage {
    // for demonstration purposes, just a string; could be anything serialized
    std::string contents;

    template <typename Blob>
    friend bool load(Blob const& blob, SpecificMessage& msg) {
        msg.contents.assign(blob.begin(), blob.end());
        return true;
    }
};

template <typename Message> struct LazyReaderFunction {
    LazyReaderFunction(shared_blobs* table) : table_(table) {}

    using type = Message;

    Message operator()(size_t index) const {
        Message result;
        if (!load(table_->at(index), result))
            throw std::bad_cast();

        return result;
    }

  private:
    shared_blobs* table_;
};

///////
// for demo, create some data.map contens
void create_datamap() {
    bip::file_mapping::remove("data.map");
    bip::managed_mapped_file mmf(bip::open_or_create, "data.map", 1ul<<20); // even sparse file sizes limited on COLIRU
    shared_blobs* table = mmf.find_or_construct<shared_blobs>("blob_table")(mmf.get_segment_manager());

    std::ifstream ifs("main.cpp");
    std::string line;
    while (std::getline(ifs, line))
        table->emplace_back(line.begin(), line.end(), mmf.get_segment_manager());

    std::cout << "Created blob table consisting of " << table->size() << " blobs\n";
}

///////

void display_random_messages() {
    bip::managed_mapped_file mmf(bip::open_only, "data.map");
    shared_blobs* table = mmf.find_or_construct<shared_blobs>("blob_table")(mmf.get_segment_manager());

    LazyReaderFunction<SpecificMessage> load(table);
    for (int i = 0; i<10; ++i) {
        auto index = rand() % table->size();
        std::cout << "Random blob #" << index << ": '" << load(index).contents << "'\n";
    }
}

int main()
{
#ifndef CONSUMER_ONLY
    create_datamap();
#endif

    srand(time(NULL));
    display_random_messages();
}
