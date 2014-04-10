#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/functional/hash.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace bmi = boost::multi_index;
namespace bip = boost::interprocess;

struct UsersKey {
    uint64_t IMSI;
};

struct UsersVal {
    uint64_t IMSI;
};

struct HashEntry{
    UsersKey key;
    UsersVal val;
}

typedef bmi::hashed_unique<bmi::tag<struct IMSI_tag>,  bmi::member<HashEntry, uint64_t , &HashEntry::UsersKey::IMSI>,  boost::hash<uint64_t>, std::equal_to<uint64_t> > hashed_by_IMSI;


typedef 
  bmi::indexed_by<  hashed_by_IMSI > UsersKey_hash_indices;

int main()
{
    typedef boost::multi_index::multi_index_container<
      HashEntry,
      UsersKey_hash_indices>
    > GlobalHash;

    GlobalHash* hash = new GlobalHash(); // not important
    HashEntry v;
    hash->insert(v);
}
