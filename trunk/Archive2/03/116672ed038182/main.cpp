#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <tuple>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

using namespace boost::multi_index;

/** Module Load List Entry */
struct MLLEntry {
    // nSetupCmd, nFilePutCmd, nCleanupCmd, DIR_FILTER (used for deleting)
    // this quartet is the same for each file associated with a HR file
    // this also goes for the HR file itself it also is loaded or deleted
    using Column = enum Column { SetupCmd = 0, PutFileCmd = 1, CleanupCmd = 2, DirFilter = 3 };

    // quartet of commands with the N defined for std::get<N>(tuple) defined in the <code>Column</code>
    using HRQuartet = std::tuple<int32_t, int32_t, int32_t, int32_t>;

    // typedef of local, module entries
    using LoadableFilePair = std::pair<std::string, std::string>;

    /**
     * ModuleLoadList entry constructor<p>
     *
     * Each entry in the module load list consists of a command
     * quartet and a corresponding pair of loadable files (the first
     * one represents the local file system loadable file while the
     * second represents the file on the module).
     *
     * @param rQuartet  [in] quartet of command indexes - see Column
     *                  enum above for details.
     * @param rLoadablePair
     *                  [in] local-module loadable file pair associated
     *                  containing <code>rQuartet</code> commands.
     */
    explicit MLLEntry(
        const HRQuartet& rQuartet,
        const LoadableFilePair& rLoadablePair)
        : mQuartet(rQuartet)
        , mLoadablePair(rLoadablePair)
    {}

    // copy constructor - not allowed
    MLLEntry(const MLLEntry& rhs) = delete;

    // move constructor
    MLLEntry(MLLEntry&& rhs)
        : mQuartet(std::move(rhs.mQuartet))
        , mLoadablePair(std::move(rhs.mLoadablePair))
    {}

    // non-throwing copy-and-swap idiom unified assignment
    inline MLLEntry& operator=(MLLEntry rhs) {
        rhs.swap(*this);
        return *this;
    }

    // non-throwing-swap idiom
    inline void swap(MLLEntry& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // swap base members
        //Base::swap(rhs);
        // swap members here
        swap(mQuartet, rhs.mQuartet);
        swap(mLoadablePair, rhs.mLoadablePair);
    }

    // destructor
    virtual ~MLLEntry() = default;

    // ordering operator
    inline bool operator<(const MLLEntry& rhs) const {
        // compare tuples in left to right order using operator<()
        return std::tie(mQuartet, mLoadablePair) <
            std::tie(rhs.mQuartet, rhs.mLoadablePair);
    }

    // equality operator
    inline bool operator==(const MLLEntry& rhs) const {
        return mQuartet == rhs.mQuartet && 
            mLoadablePair == rhs.mLoadablePair;
    }

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] Module Load List entry to send to the
     *               output stream.
     *
     * @return a reference to the updated stream
     */
    friend std::ostream& operator << (
        std::ostream& os, const MLLEntry& rhs) {
        os  << "["
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getSetupCmd() << ","  // nSetupCmd
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getPutFileCmd() << ","  // nFilePutCmd
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getCleanupCmd() << ","  // nCleanupCmd
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getDirFilter() << "] (" // DIR_FILTER
            << rhs.mLoadablePair.first << "<->"
            << rhs.mLoadablePair.second << ")";
        return os;
    }

    // nSetupCmd getter
    inline int32_t getSetupCmd() const {
        return std::get<MLLEntry::SetupCmd>(mQuartet);
    }

    // nPutFileCmd getter
    inline int32_t getPutFileCmd() const {
        return std::get<MLLEntry::PutFileCmd>(mQuartet);
    }

    // nCleanupCmd getter
    inline int32_t getCleanupCmd() const {
        return std::get<MLLEntry::CleanupCmd>(mQuartet);
    }

    // DIR_FILTER getter
    inline int32_t getDirFilter() const {
        return std::get<MLLEntry::DirFilter>(mQuartet);
    }

    HRQuartet mQuartet;
    LoadableFilePair mLoadablePair;
};

struct MyStruct {
    int a, b, c;
};

struct Tag1;
struct Tag2;

typedef multi_index_container <
    MyStruct
    , indexed_by <
        hashed_non_unique <
            tag<Tag1>
            , composite_key <
                MyStruct
                , member<MyStruct, int, &MyStruct::a>
                , member<MyStruct, int, &MyStruct::b>
            >
        >
        , hashed_non_unique <
            tag<Tag2>
            , composite_key <
                MyStruct
                , member<MyStruct, int, &MyStruct::a>
                , member<MyStruct, int, &MyStruct::b>
                , member<MyStruct, int, &MyStruct::c>
            >
        >
    >
> MyContainer;

struct dirfilter {};
struct composite {};

using IndexedFileInfo = boost::multi_index::multi_index_container<
    // the Value type stored in this multi indexed container
    MLLEntry
    // primary unique ordering index - no duplicate entries allowed
    // requires MLLEntry::operator<() to support sorting
    , indexed_by <
        ordered_unique < identity< MLLEntry > >
        // composite key ordered using nSetupCmd->nPutFileCmd->nCleanupCmd
        , ordered_non_unique<
            tag<composite>
            , composite_key <
                MLLEntry
                , const_mem_fun<MLLEntry, int32_t, &MLLEntry::getSetupCmd>
                , const_mem_fun<MLLEntry, int32_t, &MLLEntry::getPutFileCmd>
                , const_mem_fun<MLLEntry, int32_t, &MLLEntry::getCleanupCmd>
            >
        >
        // sort by less<int32_t> on mDirFilter
        , ordered_non_unique< 
            tag<dirfilter>
            , const_mem_fun<MLLEntry, int32_t, &MLLEntry::getDirFilter>
        >
    >
>;


int main()
{
    std::map<int32_t, MyContainer> containerMap;
    std::map<int32_t, IndexedFileInfo> indexedFileInfoMap;
    MyContainer c;

    MyContainer::index<Tag1>::type& index1 = c.get<Tag1>();
    MyContainer::index<Tag2>::type& index2 = c.get<Tag2>();

    //! Add some values
    for (int i = 0; i < 10; ++i) {
        MyStruct s = { i, i * 2, i * 3 };
        c.insert(s);
    }

    auto loop = [](const MyStruct& s){ std::cout << "{ " << s.a << ", " << s.b << ", " << s.c << " }" << std::endl; };

    // Search in container
    bool useIndex1 = true;
    if (useIndex1)
    {
        auto range = std::make_pair(index1.begin(), index1.end());
        std::for_each(range.first, range.second, loop);
    }
    else
    {
        auto range = std::make_pair(index1.begin(), index1.end());
        std::for_each(range.first, range.second, loop);
    }

    // Loop through range
    //for (auto i = range.first; i != range.second; ++i)

    return 0;
}
