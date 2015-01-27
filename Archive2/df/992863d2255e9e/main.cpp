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
#include <boost/multi_index/ordered_index.hpp>
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

using MyContainer = multi_index_container <
    // the Value type stored in this multi indexed container
    MyStruct
    , indexed_by <
        ordered_non_unique <
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
>;

struct composite {};
struct dirfilter {};

using IndexedFileInfo = multi_index_container<
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
                MLLEntry,                
                boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getSetupCmd>,
                boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getPutFileCmd>,
                boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getCleanupCmd>
            >
        >
        // sort by less<int> on mDirFilter
        , ordered_non_unique<
            tag<dirfilter>
            , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getDirFilter>
        >
    >
>;


int main()
{
    IndexedFileInfo c1;
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_08_12_23 = {
        MLLEntry::LoadableFilePair("004.txt", "004.txt"),
        MLLEntry::LoadableFilePair("005.txt", "005.txt"),
        MLLEntry::LoadableFilePair("005.txt", "005.txt"),
    };

    // emplace construct MLLEntries
    for (const auto& next : fileInfo_03_08_12_23) {
        c1.emplace(MLLEntry::HRQuartet(3, 8, 12, 23), next);
    }

    IndexedFileInfo c2(std::move(c1));
    IndexedFileInfo::index<composite>::type& index3 = c2.get<composite>();
    IndexedFileInfo::index<composite>::type& index4 = c1.get<composite>();     

    std::cout << "IndexedFileInfo moved into c2" << std::endl;
    std::cout << "=============================" << std::endl;
    auto range = std::make_pair(index3.begin(), index3.end());
    std::copy(range.first, range.second,
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "IndexedFileInfo moved from c1" << std::endl;
    std::cout << "=============================" << std::endl;
    auto range1 = std::make_pair(index4.begin(), index4.end());
    std::copy(range1.first, range1.second,
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    return 0;
}
