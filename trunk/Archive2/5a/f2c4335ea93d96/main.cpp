#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <iostream>

using namespace boost::interprocess;
namespace bmi = boost::multi_index;

typedef managed_shared_memory::allocator<char>::type char_allocator;
typedef basic_string<char, std::char_traits<char>, char_allocator> shm_string;

// Data to insert in shared memory
struct tickerUpdateInfo {
  shm_string id;
  shm_string symbol;
  int last_update_time;

  tickerUpdateInfo(const char *id_, const char *symbol_, int last_update_time_,
                   const char_allocator &a)
      : id(id_, a), symbol(symbol_, a), last_update_time(last_update_time_) {}

  tickerUpdateInfo &operator=(const tickerUpdateInfo &other) {
    if (this != &other) {
      id = other.id;
      symbol = other.symbol;
      last_update_time = other.last_update_time;
    }
    return *this;
  }
};

std::ostream &operator<<(std::ostream &os, const tickerUpdateInfo &obj) {
  // write obj to stream
  os << obj.id << " ";
  os << obj.symbol << " ";
  os << obj.last_update_time << " " << std::endl;
  return os;
}

// Tags
struct id {};
struct symbol {};
struct last_update_time {};

    struct my_generic_less
    {
        template<typename S1, typename S2>
        bool operator()(S1 const& a, S2 const& b) const {
            return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) < 0;
        }
    };

    // Define a multi_index_container of tickerUpdateInfos with following indices:
    //   - a unique index sorted by tickerUpdateInfo::id,
    //   - a unique index sorted by tickerUpdateInfo::symbol,
    //   - a non-unique index sorted by tickerUpdateInfo::last_update_time.
    typedef bmi::multi_index_container<
        tickerUpdateInfo,
        bmi::indexed_by<
            bmi::ordered_unique<
                bmi::tag<id>,
                BOOST_MULTI_INDEX_MEMBER(tickerUpdateInfo, shm_string, id)>,
            bmi::ordered_unique<
                bmi::tag<symbol>,
                BOOST_MULTI_INDEX_MEMBER(tickerUpdateInfo, shm_string, symbol),
                my_generic_less >,
            bmi::ordered_non_unique<bmi::tag<last_update_time>,
                                    BOOST_MULTI_INDEX_MEMBER(tickerUpdateInfo, int,
                                                            last_update_time)> >,
        managed_shared_memory::allocator<tickerUpdateInfo>::type>
    tickerUpdateInfo_set;

int main() {
  // Remove shared memory on construction and destruction
  struct shm_remove {
    shm_remove() { shared_memory_object::remove("MySharedMemory"); }
    ~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
  } remover;

  // Create shared memory
  managed_shared_memory segment(create_only, "MySharedMemory", 65536);

  // Construct the multi_index in shared memory
  tickerUpdateInfo_set *es =
      segment.construct<tickerUpdateInfo_set>(
          "TickerUpdateContainer") // Container's name in shared memory
      (tickerUpdateInfo_set::ctor_args_list(),
       segment.get_allocator<tickerUpdateInfo>()); // Ctor parameters

  // Now insert elements
  char_allocator ca(segment.get_allocator<char>());
  es->insert(tickerUpdateInfo("0", "Joe", 31, ca));
  es->insert(tickerUpdateInfo("1", "Robert", 27, ca));
  es->insert(tickerUpdateInfo("2", "John", 36, ca));
  const tickerUpdateInfo_set::nth_index<1>::type &name_index = (*es).get<1>();
  std::cout << "Before update " << std::endl;
  std::copy(name_index.begin(), name_index.end(),
            std::ostream_iterator<tickerUpdateInfo>(std::cout));

  typedef tickerUpdateInfo_set::index<symbol>::type
  ticker_update_info_set_by_symbol;
  ticker_update_info_set_by_symbol &nm_index = (*es).get<symbol>();
  ticker_update_info_set_by_symbol::iterator it;

  it = nm_index.find(shm_string("Joe", ca)); // simple approach, not efficient
  it = nm_index.find(std::string("Joe"));    // using my_generic_less
  
  //ticker_update_info_set_by_symbol::iterator it = nm_index.find("Joe");
  tickerUpdateInfo ticker_info = *it;
  ticker_info.symbol = "Deb";        // update key
  nm_index.replace(it, ticker_info); // update her record
  std::cout << "After update " << std::endl;
  std::copy(nm_index.begin(), nm_index.end(),
            std::ostream_iterator<tickerUpdateInfo>(std::cout));
  return 0;
}
