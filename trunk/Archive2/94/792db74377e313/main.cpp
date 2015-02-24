#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <iomanip>

#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index_container.hpp>

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

struct dirfilter {};
struct composite {};

using IndexedFileInfo = boost::multi_index::multi_index_container<
    // the Value type stored in this multi indexed container
    MLLEntry
    // primary unique ordering index - no duplicate entries 
    // allowed.  Requires MLLEntry::operator<() to support 
    // sorting & MLLEntry::operator==() to support container 
    // equality comparisons
    , boost::multi_index::indexed_by <
        boost::multi_index::ordered_unique <
            boost::multi_index::identity< MLLEntry > 
        >
        // composite key ordered using nSetupCmd->nPutFileCmd->nCleanupCmd
        , boost::multi_index::ordered_non_unique<boost::multi_index::tag<composite>
            , boost::multi_index::composite_key <
                MLLEntry
                , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getSetupCmd>
                , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getPutFileCmd>
                , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getCleanupCmd>
            >
        >
        // sort by less<int> on mDirFilter
        , boost::multi_index::ordered_non_unique<boost::multi_index::tag<dirfilter>
            , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getDirFilter>
        >
    >
>;

int main()
{
    // this is the sort of behavior I need where I can specify multiple indexes
    std::vector<MLLEntry::LoadableFilePair> fileInfo_01_05_10_21 = {
        MLLEntry::LoadableFilePair("xxx.txt", "xxx.txt"),
        MLLEntry::LoadableFilePair("yyy.txt", "yyy.txt")
    };

    // different setup/cleanup(02/11) identical put(05)
    std::vector<MLLEntry::LoadableFilePair> fileInfo_02_05_11_22 = {
        MLLEntry::LoadableFilePair("abc.txt", "abc.txt"),
        MLLEntry::LoadableFilePair("def.txt", "def.txt")
    };

    // completely different quartet
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_06_12_23 = {
        MLLEntry::LoadableFilePair("ghi.txt", "ghi.txt"),
        MLLEntry::LoadableFilePair("jkl.txt", "jkl.txt")
    };

    // identical setup/cleanup (03/12), different put(07)
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_07_12_23 = {
        MLLEntry::LoadableFilePair("001.txt", "001.txt"),
        MLLEntry::LoadableFilePair("002.txt", "002.txt"),
        MLLEntry::LoadableFilePair("003.txt", "003.txt")
    };

    // identical setup/cleanup (03/12), different put(08)
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_08_12_23 = {
        MLLEntry::LoadableFilePair("004.txt", "004.txt"),
        MLLEntry::LoadableFilePair("005.txt", "005.txt"),
        MLLEntry::LoadableFilePair("006.txt", "006.txt")
    };

    std::cout << "IndexedFileInfo inserting entries" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    IndexedFileInfo indexedFileInfo;
    // emplace construct MLLEntries
    for (const auto& next : fileInfo_01_05_10_21) {
        const auto& res = indexedFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(1, 5, 10, 21), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_02_05_11_22) {
        const auto& res = indexedFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(2, 5, 11, 22), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_03_06_12_23) {
        const auto& res = indexedFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(3, 6, 12, 23), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_03_08_12_23) {
        const auto& res = indexedFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(3, 8, 12, 23), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    // duplicate entries should be rejected due to the 
    // unique identity key in the IndexedFileInfo
    for (const auto& next : fileInfo_03_08_12_23) {
        const auto& res = indexedFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(3, 8, 12, 23), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }

    for (const auto& next : indexedFileInfo) {
        std::cout << next << std::endl;
    }

    // get a view to index #0 (default) ordered unique index
    // this should sequence through all the entries in 
    // MLLEntry::operator<() unique order
    std::cout << "IndexedFileInfo identity order" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(indexedFileInfo.cbegin(), indexedFileInfo.cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "IndexedFileInfo by DIR_FILTER" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(indexedFileInfo.get<dirfilter>().cbegin(),
        indexedFileInfo.get<dirfilter>().cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList - composite key order" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(indexedFileInfo.get<composite>().cbegin(),
        indexedFileInfo.get<composite>().cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList (DIR_FILTER >= 22)" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(indexedFileInfo.get<dirfilter>().lower_bound(22),
        indexedFileInfo.get<dirfilter>().cend(), 
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    // this range should return fileInfo1224 & fileInfo3125
    std::cout << "ModuleLoadList (lb22<->ub23)" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(indexedFileInfo.get<dirfilter>().lower_bound(22),
        indexedFileInfo.get<dirfilter>().upper_bound(23),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList (DIR_FILTER == 21)" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    const auto& range = indexedFileInfo.get<dirfilter>().equal_range(21);
    std::copy(range.first, range.second,
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList Sequencing" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    for (auto it = indexedFileInfo.get<composite>().cbegin();
        it != indexedFileInfo.get<composite>().cend();) {
        std::stringstream ss;
        ss << "run->nSetupCmd[" << it->getSetupCmd() << "]" << std::endl;
        // find next range with current nSetupCmd & nPutFileCmd (cleanup ignored 
        // as should be identical for each SetupCmd/nPutFileCmd combination)
        const auto& spcRange = indexedFileInfo.get<composite>().equal_range(
            boost::make_tuple(it->getSetupCmd(), it->getPutFileCmd()/*, it->getCleanupCmd()*/));
        // print out all LoadablePairs with equal nSetupCmd, nPutFileCmd
        std::copy(spcRange.first, spcRange.second,
            std::ostream_iterator<MLLEntry>(ss, "\n"));
        ss << "run->nCleanupCmd[" << it->getCleanupCmd() << "]" << std::endl;
        std::cout << ss.str();
        // advance the iterator to the next group of nSetupCmds
        it = spcRange.second;
    }
}
