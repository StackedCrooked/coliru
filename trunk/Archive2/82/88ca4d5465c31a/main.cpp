///////////////////////////////////////////////////////////////////////////
// ShmTypedefs.h
#pragma once

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index_container.hpp>

namespace bmi = boost::multi_index;
namespace bip = boost::interprocess;

//the strings also need to be assigned from the shared memory
typedef bip::allocator<char, bip::managed_shared_memory::segment_manager> CharAllocator;
typedef bip::basic_string<char, std::char_traits<char>, CharAllocator> SharedString;

struct Record {
    SharedString outerkey, innerkey;
    int value;

    Record(std::string okey, std::string ikey, int value, CharAllocator alloc) : 
        outerkey(okey.begin(), okey.end(), alloc), 
        innerkey(ikey.begin(), ikey.end(), alloc), 
        value(value) 
    {}
    Record(CharAllocator alloc) : outerkey(alloc), innerkey(alloc), value() {}
};

typedef bip::allocator<Record, bip::managed_shared_memory::segment_manager> RecordAllocator;

typedef bmi::multi_index_container<Record,
    bmi::indexed_by<
        bmi::ordered_non_unique<bmi::tag<struct primary_index>,
            bmi::composite_key<Record,
                bmi::member<Record, SharedString, &Record::outerkey>,
                bmi::member<Record, SharedString, &Record::innerkey>,
                bmi::member<Record, int,          &Record::value>
            > > >, 
        RecordAllocator> Table;

// End ShmTypedefs.h
///////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/range/iterator_range.hpp>

static constexpr char const* SHARED_MEM_NAME   = "SharedMemoryName";
static constexpr char const* SHARED_TABLE_NAME = "MyTable";

void writer()
{
    // remove earlier existing SHM
    bip::shared_memory_object::remove(SHARED_MEM_NAME);

    // create new
    bip::managed_shared_memory segment(bip::create_only,SHARED_MEM_NAME, 65536);
    CharAllocator char_alloc(segment.get_segment_manager());

    Table* table = segment.construct<Table>(SHARED_TABLE_NAME)(RecordAllocator{segment.get_segment_manager()});
    table->emplace("case1", "inner_case1", 2030, char_alloc);
    table->emplace("case1", "inner_case3", 2034, char_alloc);
    table->emplace("case2", "inner_case2", 2031, char_alloc);

    for (auto const& r : *table)
        std::cout << r.outerkey << ", " << r.innerkey << ", " << r.value << "\n";
}

void reader() {
    try {
        bip::managed_shared_memory segment(bip::open_or_create,SHARED_MEM_NAME, 65536);
        CharAllocator char_alloc(segment.get_segment_manager());

        Table* table = nullptr;
        size_t size  = 0;
        boost::tie(table, size) = segment.find<Table>(SHARED_TABLE_NAME);
        std::cout << "number of entries: " << size << std::endl;

        for (Record const& r : boost::make_iterator_range(table->equal_range(SharedString("case1", char_alloc))))
            std::cout << "symbol " << r.innerkey << " time " << r.value << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "error  " << e.what() << std::endl;
        bip::shared_memory_object::remove(SHARED_MEM_NAME);
    }
}

int main() {
    writer();
    reader();
}
