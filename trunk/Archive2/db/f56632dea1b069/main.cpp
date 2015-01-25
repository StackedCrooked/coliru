#include <boost/container/scoped_allocator.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/string.hpp>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace Shared {
    namespace bip = boost::interprocess;
    namespace bc  = boost::container;

    using msm_t = bip::managed_shared_memory;
    using mutex = bip::interprocess_sharable_mutex;
    using guard = boost::lock_guard<mutex>;

    template <typename T> using allocator    = bc::scoped_allocator_adaptor<
                                                   bip::allocator<T, msm_t::segment_manager>
                                               >;
    template <typename T> using vector       = bc::vector<T, allocator<T> >;
    template <typename T> using basic_string = bc::basic_string<T, std::char_traits<T>, allocator<T> >;

    using string  = basic_string<char>;
    using wstring = basic_string<wchar_t>;
}

namespace SWMR {
    namespace bip = boost::interprocess;
    namespace bc  = boost::container;

    class Segment {
      public:
        // LockableObject, base template
        //
        // LockableObject contains a `Shared::mutex` and an object of type T
        template <typename T, typename Enable = void> struct LockableObject;

        // Partial specialization for the case when the wrapped object cannot
        // use the shared allocator: the constructor is just forwarded
        template <typename T>
        struct LockableObject<T, typename boost::disable_if<bc::uses_allocator<T, Shared::allocator<T> >, void>::type>
        {
            template <typename... CtorArgs>
            LockableObject(CtorArgs&&... args) : object(std::forward<CtorArgs>(args)...) {}
            LockableObject() : object() {}

            mutable Shared::mutex mutex;
            T object;

          private:
            friend class Segment;
            template <typename... CtorArgs>
            static LockableObject& locate_by_name(Shared::msm_t& msm, const char* tag, CtorArgs&&... args) {
                return *msm.find_or_construct<LockableObject<T> >(tag)(std::forward<CtorArgs>(args)...);
            }
        };

        // Partial specialization for the case where the contained object can
        // use the shared allocator;
        //
        // Construction (using locate_by_name) adds the allocator as the last
        // argument.
        template <typename T>
        struct LockableObject<T, typename boost::enable_if<bc::uses_allocator<T, Shared::allocator<T> >, void>::type>
        {
            using allocator_type = Shared::allocator<void>;

            template <typename... CtorArgs>
            LockableObject(CtorArgs&&... args) : object(std::forward<CtorArgs>(args)...) {}
            LockableObject(allocator_type alloc = {}) : object(alloc) {}

            mutable Shared::mutex mutex;
            T object;

          private:
            friend class Segment;
            template <typename... CtorArgs>
            static LockableObject& locate_by_name(Shared::msm_t& msm, const char* tag, CtorArgs&&... args) {
                return *msm.find_or_construct<LockableObject>(tag)(std::forward<CtorArgs>(args)..., Shared::allocator<T>(msm.get_segment_manager()));
            }
        };

        Segment(std::string const& name, size_t capacity = 1024*1024) // default 1 MiB
            : _msm(bip::open_or_create, name.c_str(), capacity)
        {
        }

        template <typename T, typename... CtorArgs>
        LockableObject<T>& getLockable(char const* tag, CtorArgs&&... args) {
            return LockableObject<T>::locate_by_name(_msm, tag, std::forward<CtorArgs>(args)...);
        }

    private:
        Shared::msm_t _msm;
    };
}

#include <vector>

static char const* const APP_UUID = "249f3878-3ddf-4473-84b2-755998952da1";

struct UserData {
    using allocator_type = Shared::allocator<void>;
    using String         = Shared::string;

    UserData(allocator_type alloc) : text(alloc) { }
    UserData(int i, String t) : i(i), text(t) { }
    UserData(UserData const& other, allocator_type alloc) : i(other.i), text(other.text, alloc) { }

    template <typename T>
        UserData(int i, T&& t, allocator_type alloc)
            : i(i), text(std::forward<T>(t), alloc)
        { }

    // data
    int i;
    String text;
};

#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>
#include <iostream>

int main() {
    using IntVec = Shared::vector<int>;
    using UdtVec = Shared::vector<UserData>;

    boost::interprocess::shared_memory_object::remove(APP_UUID); // for demo

    // server code
    {
        SWMR::Segment server(APP_UUID);

        auto& s_ints = server.getLockable<IntVec>("ints", std::initializer_list<int> {1,2,3,4,5,6,7,42}); // allocator automatically added
        auto& s_udts = server.getLockable<UdtVec>("udts");

        {
            Shared::guard lk(s_ints.mutex);
            boost::fill(s_ints.object, 99);

            // or manipulate the vector. Any allocations go to the shared memory segment automatically
            s_ints.object.push_back(42);
            s_ints.object.assign(20, 42);
        }

        {
            Shared::guard lk(s_udts.mutex);
            s_udts.object.emplace_back(1, "one"); // allocates the string in shared memory, and the UserData element too
        }
    }

    // client code
    {
        SWMR::Segment client(APP_UUID);

        auto& c_ints = client.getLockable<IntVec>("ints", 20, 999); // the ctor arguments are ignored here
        auto& c_udts = client.getLockable<UdtVec>("udts");

        {
            Shared::guard lk(c_ints.mutex);
            IntVec& ivec = c_ints.object;
            assert(boost::equal(std::vector<int>(20, 42), ivec));
        }

        {
            Shared::guard lk(c_udts.mutex);
            BOOST_FOREACH(UserData& udt, c_udts.object)
                std::cout << udt.i << "\t'" << udt.text << "'\n";
        }
    }
}
