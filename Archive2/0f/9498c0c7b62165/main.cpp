#include <boost/flyweight.hpp>
#include <boost/flyweight/no_tracking.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/range/any_range.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include <string>
#include <chrono>
#include <iostream>
#include <numeric>

namespace bmi = boost::multi_index;

#define USE_FLYWEIGHT 0 // 0: none 1: full 2: no tracking 3: no tracking no locking
//#define OPTIMIZE_ATOMS

#ifdef OPTIMIZE_ATOMS
static size_t atoms_requested = 0;
static size_t atoms_unique_created = 0;

typedef wchar_t const* watom;
typedef char    const* atom;

template <typename Char, typename CharT=std::char_traits<Char>, typename Alloc=std::allocator<Char> >
Char const* do_make_atom(std::basic_string<Char, CharT, Alloc> const& s)
{
    static std::set<std::basic_string<Char, CharT, Alloc> > s_atoms;
    atoms_requested += 1;

    auto it = s_atoms.find(s);
    if (it != s_atoms.end())
        return it->c_str();

    atoms_unique_created += 1;
    return s_atoms.insert(s).first->c_str();
}

wchar_t const* make_watom(std::wstring const& s) { return do_make_atom(s); }
char    const* make_atom (std::string  const& s) { return do_make_atom(s); }

#else
typedef std::wstring watom;
typedef std::string atom;

template <typename T> T&& make_atom(T&& v) { return std::forward<T>(v); }
template <typename T> T&& make_watom(T&& v) { return std::forward<T>(v); }
#endif

struct DataKey {
    bool operator==(const DataKey &rhs) const {
        return (m_intData01 == rhs.m_intData01 && 
                m_intData02 == rhs.m_intData02 &&
                m_strData03 == rhs.m_strData03);
    }

    int m_intData01;
    int m_intData02;
    watom m_strData03;

#if USE_FLYWEIGHT == 0
    DataKey&       get()       { return *this; }
    DataKey const& get() const { return *this; }
#endif
};

#if USE_FLYWEIGHT == 0
typedef DataKey Key;
#elif USE_FLYWEIGHT == 1
typedef boost::flyweight<DataKey> Key;
#elif USE_FLYWEIGHT == 2
typedef boost::flyweight<DataKey, boost::flyweights::no_tracking> Key;
#elif USE_FLYWEIGHT == 3
typedef boost::flyweight<DataKey, boost::flyweights::no_tracking, boost::flyweights::no_locking> Key;
#endif

struct Data {
    Data(DataKey key = {}) : m_key(key) {}

    Data(Data &&rhs)              = default;
    Data(const Data &)            = delete;
    Data &operator=(Data &&rhs)   = default;
    Data &operator=(const Data &) = delete;

    bool operator==(const Data &rhs) const { return (rhs.m_intMem03 == m_intMem03); }
    bool operator< (const Data &rhs) const { return (rhs.m_intMem03 <  m_intMem03); }

    int   getIntData01() const { return m_key.get().m_intData01; }
    int   getIntData02() const { return m_key.get().m_intData02; }
#   ifdef OPTIMIZE_ATOMS
    watom getStrData03() const { return m_key.get().m_strData03; }
#   else
    const watom& getStrData03() const { return m_key.get().m_strData03; }
#   endif

    Key          m_key;
    std::wstring m_strMem01;
    std::string  m_strMem02;
    int          m_intMem03  = -1;
    int          m_intMem04  = 0;
    int          m_intMem05  = 0;
    int          m_intMem06  = 0;
    int          m_intMem07  = -1;
    bool         m_boolMem08 = false;
    bool         m_boolMem09 = false;
};

typedef boost::multi_index_container <Data,
    bmi::indexed_by<
        bmi::ordered_non_unique<
            bmi::tag<struct byKey>,
            bmi::composite_key<Data,
                bmi::const_mem_fun<Data, int,   &Data::getIntData01> ,
                bmi::const_mem_fun<Data, int,   &Data::getIntData02> ,
#if defined(OPTIMIZE_ATOMS)
                bmi::const_mem_fun<Data, watom, &Data::getStrData03>>
#else
                bmi::const_mem_fun<Data, watom const&, &Data::getStrData03>>
#endif
            >,
            bmi::ordered_non_unique<
                bmi::tag<struct byMem>,
                bmi::member<Data, int, &Data::m_intMem03>
            >
        >
    > DataContainer;

#if 1
typedef boost::any_range<Data, boost::bidirectional_traversal_tag, const Data &, std::ptrdiff_t> DataRange;
#else
typedef boost::iterator_range<DataContainer::index<byKey>::type::const_iterator> DataRange;
#endif

#if USE_FLYWEIGHT == 0
#else
size_t hash_value(const DataKey &key) {
    size_t seed = 0;
    boost::hash_combine(seed, key.m_intData02);
    boost::hash_combine(seed, key.m_intData01);
    boost::hash_combine(seed, key.m_strData03);
    return seed;
}
#endif

class MICTest {
    public:
        MICTest() : m_data() {}

        void deepTest() {
            std::cout << "Populating data." << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            populateDeep();

            auto duration = std::chrono::high_resolution_clock::now() - start;
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms for populateDeep()." << std::endl;

            std::cout << "Running " << __FUNCTION__ << std::endl << std::endl;
            {
                std::cout << "Checking getVersionData perf." << std::endl;

                start = std::chrono::high_resolution_clock::now();

                DataRange data = getData(234567, 123456, L"DeepTest");

                duration = std::chrono::high_resolution_clock::now() - start;
                std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms for getData()." << std::endl;

                start = std::chrono::high_resolution_clock::now();

                auto res = std::accumulate(
                        data.begin(), data.end(), 0ll,
                        [&](long long init, const Data &rhs) { return init + rhs.m_intMem07; });

                duration = std::chrono::high_resolution_clock::now() - start;
                std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms for all calulations, res=" << res << std::endl
                    << std::endl;
            }
        }

    private:
        void populateDeep() {
            m_data.clear();
            int counter = 0;
            for (auto i = 0; i < 3; ++i) {
                for (auto j = 0; j < 3; ++j) {
                    for (auto k = 0; k < 11111; ++k, ++counter) {
                        Data data({234567, 123456, make_watom(L"DeepTest")});
                        data.m_strMem01 = make_watom(L"TestTestTest");
                        data.m_strMem02 = make_atom("Test");
                        data.m_intMem03 = 456789 + counter;
                        data.m_intMem04 = (i + j + k) % 100;
                        data.m_intMem07 = 345678 + i + j + k;
                        data.m_boolMem08 = ((i + j + k) % 2 == 1);
                        data.m_boolMem09 = ((i + j + k) % 3 == 1);
                        m_data.insert(std::move(data));
                    }
                }
            }
            std::cout << "Index size: " << m_data.size() << std::endl;
        }

        DataRange getData(int intData01, int intData02, const std::wstring &strData03) const {
            return m_data.get<byKey>().equal_range(boost::make_tuple(intData01, intData02, make_watom(strData03)));
        }

        DataContainer m_data;
};

int main() {
    {
        MICTest test3;
        test3.deepTest();
        //std::cin.get();
    }

    std::cout << "===============================================================\n";
}
