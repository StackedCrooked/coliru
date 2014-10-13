#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace bip = boost::interprocess;

using ShMemRef = boost::shared_ptr<bip::managed_shared_memory>;
template <typename T> using shm_alloc = bip::allocator<T, bip::managed_shared_memory::segment_manager>;
template <typename K, typename V> using shared_map = bip::map<K, V, std::less<K>, shm_alloc<std::pair<K const, V> > >;

class Helper
{
  public:
    using inner_alloc = shm_alloc<std::pair<int, ShMemRef>>;
    Helper(inner_alloc const& instance) : shm(instance) {}
  private:
    int i;
    shared_map<int, ShMemRef> shm;
};

int main()
{
    ShMemRef shmInfo = boost::make_shared<bip::managed_shared_memory>(bip::open_or_create, "Main", 1024);

    using outer_alloc = shm_alloc<std::pair<const int, Helper>>;
    outer_alloc oa_instance(shmInfo->get_segment_manager());

    shared_map<int, Helper>* myHelpers = shmInfo->construct<shared_map<int, Helper>>("Memory")(oa_instance);

    Helper::inner_alloc ia_instance(shmInfo->get_segment_manager());
    Helper helper1(ia_instance), helper2(ia_instance), helper3(ia_instance);
    myHelpers->emplace(1, helper1);
    myHelpers->emplace(2, helper2);
    myHelpers->emplace(3, helper3);
}
