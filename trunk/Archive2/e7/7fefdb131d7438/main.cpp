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
    uint32_t IMEI;
};

typedef bmi::hashed_unique<bmi::tag<struct IMSI_tag>,  bmi::member<UsersKey, uint64_t , &UsersKey::IMSI>,  boost::hash<uint64_t>, std::equal_to<uint64_t> > hashed_by_IMSI;
typedef bmi::hashed_unique<bmi::tag<struct IMEI_tag>,  bmi::member<UsersKey, uint32_t , &UsersKey::IMEI>,  boost::hash<uint32_t>, std::equal_to<uint64_t> > hashed_by_IMEI;

typedef 
  bmi::indexed_by<
  //boost::multi_index::hashed_unique< boost::multi_index::identity<UsersKey> >,
        hashed_by_IMSI,
        hashed_by_IMEI
        > UsersKey_hash_indices;

int main()
{
    typedef boost::multi_index::multi_index_container<
      UsersKey,
      UsersKey_hash_indices    
    > GlobalHash;

    GlobalHash* hash = new GlobalHash(); // not important
    UsersKey v;
    hash->insert(v);
}
