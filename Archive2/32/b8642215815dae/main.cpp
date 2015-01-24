#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/serialization/serialization.hpp>

namespace bip = boost::interprocess;

namespace SWMR {
    static struct server_mode_t {} const/*expr*/ server_mode = server_mode_t();
    static struct client_mode_t {} const/*expr*/ client_mode = client_mode_t();

    typedef bip::interprocess_sharable_mutex mutex;
    typedef boost::lock_guard<mutex> guard;

    template <typename T, size_t N> struct SharedMemArray {
        SharedMemArray(server_mode_t, std::string const& name) 
          : isManager(true), _name(name), 
            _shm(do_create(_name.c_str())),
            _region(_shm, bip::read_write)
        {
            _data = new (_region.get_address()) data_t;
        }

        SharedMemArray(client_mode_t, std::string const& name) 
          : isManager(false), _name(name),
            _shm(do_open(_name.c_str())),
            _region(_shm, bip::read_write),
            _data(static_cast<data_t*>(_region.get_address()))
        {
            assert(sizeof(data_t) == _region.get_size());
        }

    private:
        BOOST_STATIC_ASSERT(boost::is_pod<T>::value);

        typedef bip::shared_memory_object shm_t;
        struct data_t { 
            mutable mutex mtx;
            T DataPtr[N];
        };

        bool               isManager;
        const std::string  _name;
        shm_t              _shm;
        bip::mapped_region _region;
        data_t            *_data;

        // functions to manage the shared memory
        shm_t static do_create(char const* name) {
            shm_t::remove(name);
            shm_t result(bip::create_only, name, bip::read_write);
            result.truncate(sizeof(data_t));
            return boost::move(result);
        }

        shm_t static do_open(char const* name) {
            return shm_t(bip::open_only, name, bip::read_write);
        }

      public:
        mutex& get_mutex() const { return _data->mtx; }

        typedef T       *iterator;
        typedef T const *const_iterator;

        iterator data()                { return _data->DataPtr; }
        const_iterator data() const    { return _data->DataPtr; }

        iterator begin()               { return data(); }
        const_iterator begin() const   { return data(); }

        iterator end()                 { return begin() + N; }
        const_iterator end() const     { return begin() + N; }

        const_iterator cbegin() const  { return begin(); }
        const_iterator cend() const    { return end(); }
    };
}

#include <vector>

static const std::string APP_UUID = "61ab4f43-2d68-46e1-9c8d-31d577ce3aa7";

struct UserData {
    int   i;
    float f;
};

#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>

int main() {
    using namespace SWMR;
    SharedMemArray<int, 20>      s_ints   (server_mode, APP_UUID + "-ints");
    SharedMemArray<float, 72>    s_floats (server_mode, APP_UUID + "-floats");
    SharedMemArray<UserData, 10> s_udts   (server_mode, APP_UUID + "-udts");

    {
        guard lk(s_ints.get_mutex());
        boost::fill(s_ints, 42);
    }

    {
        guard lk(s_floats.get_mutex());
        boost::fill(s_floats, 31415);
    }

    {
        guard lk(s_udts.get_mutex());
        UserData udt = { 42, 3.14 };
        boost::fill(s_udts, udt);
    }

    SharedMemArray<int, 20>      c_ints   (client_mode, APP_UUID + "-ints");
    SharedMemArray<float, 72>    c_floats (client_mode, APP_UUID + "-floats");
    SharedMemArray<UserData, 10> c_udts   (client_mode, APP_UUID + "-udts");

    {
        guard lk(c_ints.get_mutex());
        assert(boost::equal(std::vector<int>(boost::size(c_ints), 42), c_ints));
    }

    {
        guard lk(c_floats.get_mutex());
        assert(boost::equal(std::vector<int>(boost::size(c_floats), 31415), c_floats));
    }

    {
        guard lk(c_udts.get_mutex());
        BOOST_FOREACH(UserData& udt, c_udts)
            std::cout << udt.i << "\t" << udt.f << "\n";
    }
}
