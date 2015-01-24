#include <boost/container/scoped_allocator.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/string.hpp>
#include <boost/container/map.hpp>
#include <boost/container/deque.hpp>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace Shared {
    namespace bip = boost::interprocess;
    namespace bc  = boost::container;

    using shm_t = bip::managed_shared_memory;
    using mutex = bip::interprocess_sharable_mutex;
    using guard = boost::lock_guard<mutex>;

    template <typename T> using allocator    = bc::scoped_allocator_adaptor<
                                                   bip::allocator<T, shm_t::segment_manager>
                                               >;
    template <typename T> using vector       = bc::vector<T, allocator<T> >;
    template <typename T> using deque        = bc::deque<T, allocator<T> >;
    template <typename T> using basic_string = bc::basic_string<T, std::char_traits<T>, allocator<T> >;

    using string  = basic_string<char>;
    using wstring = basic_string<wchar_t>;

    template <typename K, typename V, typename Cmp> using map =
        bc::map<K, V, Cmp, allocator<typename bc::map<K, V>::value_type> >;
}

namespace SWMR {
    namespace bip = boost::interprocess;

    static struct server_mode_t {} const/*expr*/ server_mode = server_mode_t();
    static struct client_mode_t {} const/*expr*/ client_mode = client_mode_t();

    template <typename T> struct SharedMemArray {

    private:
        struct data_t {
            using allocator_type = Shared::allocator<void>;

            data_t(size_t N, allocator_type alloc) : elements(alloc) { elements.resize(N); }
            data_t(allocator_type alloc)           : elements(alloc) {}

            mutable Shared::mutex mtx;
            Shared::vector<T> elements;
        };

        bool               isManager;
        const std::string  _name;
        Shared::shm_t      _shm;
        data_t            *_data;

        // functions to manage the shared memory
        Shared::shm_t static do_create(char const* name) {
            bip::shared_memory_object::remove(name);
            Shared::shm_t result(bip::create_only, name, 1ul << 20); // ~1 MiB
            return boost::move(result);
        }

        Shared::shm_t static do_open(char const* name) {
            return Shared::shm_t(bip::open_only, name);
        }

      public:
        SharedMemArray(server_mode_t, std::string const& name, size_t N = 0)
          : isManager(true), _name(name), _shm(do_create(_name.c_str()))
        {
            _data = _shm.find_or_construct<data_t>(name.c_str())(N, _shm.get_segment_manager());
        }

        SharedMemArray(client_mode_t, std::string const& name)
          : isManager(false), _name(name), _shm(do_open(_name.c_str()))
        {
            auto found = _shm.find<data_t>(name.c_str());
            assert(found.second);
            _data = found.first;
        }

        Shared::mutex&  mutex() const             { return _data->mtx; }
        Shared::vector<T>      & elements()       { return _data->elements; }
        Shared::vector<T> const& elements() const { return _data->elements; }
    };
}

#include <vector>

static const std::string APP_UUID = "93f6b721-1d34-46d9-9877-f967fea61cf2";

struct UserData {
    using allocator_type = Shared::allocator<void>;

    UserData(allocator_type alloc) : text(alloc) {}
    UserData(UserData const& other, allocator_type alloc) : i(other.i), text(other.text, alloc) {}
    UserData(int i, Shared::string t) : i(i), text(t) {}
    template <typename T> UserData(int i, T&& t, allocator_type alloc) : i(i), text(std::forward<T>(t), alloc) {}

    // data
    int   i;
    Shared::string text;
};

#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>
#include <iostream>

int main() {
    using namespace SWMR;
    SharedMemArray<int>      s_ints(server_mode, APP_UUID + "-ints", 20);
    SharedMemArray<UserData> s_udts(server_mode, APP_UUID + "-udts");
    // server code

    {
        Shared::guard lk(s_ints.mutex());
        boost::fill(s_ints.elements(), 99);

        // or manipulate the vector. Any allocations go to the shared memory segment automatically
        s_ints.elements().push_back(42);
        s_ints.elements().assign(20, 42);
    }

    {
        Shared::guard lk(s_udts.mutex());
        s_udts.elements().emplace_back(1, "one");
    }

    // client code
    SharedMemArray<int>      c_ints(client_mode, APP_UUID + "-ints");
    SharedMemArray<UserData> c_udts(client_mode, APP_UUID + "-udts");

    {
        Shared::guard lk(c_ints.mutex());
        auto& e = c_ints.elements();
        assert(boost::equal(std::vector<int>(20, 42), e));
    }

    {
        Shared::guard lk(c_udts.mutex());
        BOOST_FOREACH(UserData& udt, c_udts.elements())
            std::cout << udt.i << "\t'" << udt.text << "'\n";
    }
}
