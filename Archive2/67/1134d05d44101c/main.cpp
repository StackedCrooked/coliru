#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/container/scoped_allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <iostream>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/iterator_range.hpp>

static char const* DBASE_FNAME = "database.map";

namespace bip = boost::interprocess;

namespace shm {
    using segment_manager = bip::managed_mapped_file::segment_manager;
    template <typename T> using allocator = boost::container::scoped_allocator_adaptor<bip::allocator<T, segment_manager> >;
    template <typename T> using vector    = bip::vector<T, allocator<T> >;
}

using blob_t       = shm::vector<uint8_t>;
using shared_blobs = shm::vector<blob_t>;

struct SpecificMessage {
    // for demonstration purposes, just a string; could be anything serialized
    std::string contents;

    // trivial save/load serialization code:
    template <typename Blob>
    friend bool save(Blob& blob, SpecificMessage const& msg) {
        blob.assign(msg.contents.begin(), msg.contents.end());
        return true;
    }

    template <typename Blob>
    friend bool load(Blob const& blob, SpecificMessage& msg) {
        msg.contents.assign(blob.begin(), blob.end());
        return true;
    }
};

template <typename Message> struct LazyLoader {
    using type = Message;

    Message operator()(blob_t const& blob) const {
        Message result;
        if (!load(blob, result)) throw std::bad_cast(); // TODO custom excepion
        return result;
    }
};

///////
// for demo, create some database contents
void create_database_file() {
    bip::file_mapping::remove(DBASE_FNAME);
    bip::managed_mapped_file mmf(bip::open_or_create, DBASE_FNAME, 1ul<<20); // Even sparse file size is limited on Coliru

    shared_blobs* table = mmf.find_or_construct<shared_blobs>("blob_table")(mmf.get_segment_manager());

    std::ifstream ifs("main.cpp");
    std::string line;
    while (std::getline(ifs, line)) {
        table->emplace_back();
        save(table->back(), SpecificMessage { line });
    }

    std::cout << "Created blob table consisting of " << table->size() << " blobs\n";
}

///////

void display_random_messages() {
    bip::managed_mapped_file mmf(bip::open_only, DBASE_FNAME);
    shared_blobs* table = mmf.find_or_construct<shared_blobs>("blob_table")(mmf.get_segment_manager());

    using It = boost::transform_iterator<LazyLoader<SpecificMessage>, shared_blobs::const_reverse_iterator>;

    // for fun, let's reverse the blobs
    for (It first(table->rbegin()), last(table->rend()); first < last; first+=13)
        std::cout << "blob: '" << first->contents << "'\n";

    // any kind of random access is okay, though:
    auto random = rand() % table->size();
    SpecificMessage msg;
    load(table->at(random), msg);
    std::cout << "Random blob #" << random << ": '" << msg.contents << "'\n";
}

int main()
{
#ifndef CONSUMER_ONLY
    create_database_file();
#endif

    srand(time(NULL));
    display_random_messages();
}
