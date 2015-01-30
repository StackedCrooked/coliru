#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

using namespace boost::multi_index;

class SyncAttr {
public:
    enum Value {
        load, update, extra, insync
    };
    static const SyncAttr LOAD, UPDATE, EXTRA, INSYNC;
    // integral operator cast for switch statements (cast to named enum)
    inline operator const Value() const {
        return mValue;
    }
    // required to compare the font size
    inline bool operator>=(const SyncAttr& rhs) const {
        return mValue >= rhs.mValue;
    }
    // used to store in a set
    inline bool operator<(const SyncAttr& rhs) const {
        return mValue < rhs.mValue;
    }
    // used for comparing
    inline bool operator==(const SyncAttr& rhs) const {
        if (this != &rhs) {
            return mValue == rhs.mValue;
        } else {
            return true;
        }
    }

    // serialized version of the enum
    inline std::string getStringVal() const {
        return mStringVal;
    }

    static const std::set<SyncAttr>& getValues() {
        static std::set<SyncAttr> gValues;
        if (gValues.empty()) {
            gValues.insert(LOAD);
            gValues.insert(UPDATE);
            gValues.insert(EXTRA);
            gValues.insert(INSYNC);
        }
        return gValues;
    }

    static SyncAttr valueOf(const std::string& rStringVal) {
        for (const auto& next : getValues()) {
            if (next.getStringVal() == rStringVal) {
                return next;
            }
        }
        throw std::invalid_argument(
            "Invalid Argument: " + rStringVal);
    }
private:
    SyncAttr(
        const Value& rValue,
        const std::string& rStringVal)
        : mValue(rValue)
        , mStringVal(rStringVal)
    {}
    Value mValue;
    std::string mStringVal;
};

// STATIC VARIABLE INITIALIZATIONS
const SyncAttr SyncAttr::LOAD(SyncAttr::load, "LOAD");
const SyncAttr SyncAttr::UPDATE(SyncAttr::update, "UPDATE");
const SyncAttr SyncAttr::EXTRA(SyncAttr::extra, "EXTRA");
const SyncAttr SyncAttr::INSYNC(SyncAttr::insync, "INSYNC");

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
    //MLLEntry(const MLLEntry& rhs) = delete;
    MLLEntry(const MLLEntry& rhs) 
        : mQuartet(rhs.mQuartet)
        , mLoadablePair(rhs.mLoadablePair)
    {}
    
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
    // this is the sort of behavior I need where I can specify multiple indexes
    std::vector<MLLEntry::LoadableFilePair> fileInfo_01_05_10_21 = {
        {"xxx.txt", "xxx.txt"},
        {"yyy.txt", "yyy.txt"}
    };

    // different setup/cleanup(02/11) identical put(05)
    std::vector<MLLEntry::LoadableFilePair> fileInfo_02_05_11_22 = {
        {"abc.txt", "abc.txt"},
        {"def.txt", "def.txt"}
    };

    // completely different quartet
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_06_12_23 = {
        {"ghi.txt", "ghi.txt"},
        {"jkl.txt", "jkl.txt"}
    };

    // identical setup/cleanup (03/12), different put(07)
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_07_12_23 = {
        {"001.txt", "001.txt"},
        {"002.txt", "002.txt"},
        {"003.txt", "003.txt"}
    };

    // identical setup/cleanup (03/12), different put(08)
    std::vector<MLLEntry::LoadableFilePair> fileInfo_03_08_12_23 = {
        {"004.txt", "004.txt"},
        {"005.txt", "005.txt"},
        {"006.txt", "006.txt"}
    };

    std::cout << "IndexedFileInfo inserting entries" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    IndexedFileInfo loadFileInfo;
    // emplace construct MLLEntries
    for (const auto& next : fileInfo_01_05_10_21) {
        const auto& res = loadFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(1, 5, 10, 21), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << ": duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_02_05_11_22) {
        const auto& res = loadFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(2, 5, 11, 22), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << ": duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_03_06_12_23) {
        const auto& res = loadFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(3, 6, 12, 23), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << ": duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_03_08_12_23) {
        const auto& res = loadFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(3, 8, 12, 23), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << ": duplicate, not inserted" << std::endl;
        }
    }
    // duplicate entries should be rejected due to the 
    // unique identity key in the IndexedFileInfo
    for (const auto& next : fileInfo_03_08_12_23) {
        const auto& res = loadFileInfo.insert(MLLEntry(
            MLLEntry::HRQuartet(3, 8, 12, 23), next));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << ": duplicate, not inserted" << std::endl;
        }
    }

    // get a view to index #0 (default) ordered unique index
    // this should sequence through all the entries in 
    // MLLEntry::operator<() unique order
    std::cout << "IndexedFileInfo identity order" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(loadFileInfo.cbegin(), loadFileInfo.cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "IndexedFileInfo by DIR_FILTER" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(loadFileInfo.get<dirfilter>().cbegin(),
        loadFileInfo.get<dirfilter>().cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList - composite key order" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(loadFileInfo.get<composite>().cbegin(),
        loadFileInfo.get<composite>().cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList (DIR_FILTER >= 22)" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(loadFileInfo.get<dirfilter>().lower_bound(22),
        loadFileInfo.get<dirfilter>().cend(), 
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    // this range should return fileInfo1224 & fileInfo3125
    std::cout << "ModuleLoadList (lb22<->ub23)" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    std::copy(loadFileInfo.get<dirfilter>().lower_bound(22),
        loadFileInfo.get<dirfilter>().upper_bound(23),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList (DIR_FILTER == 21)" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    const auto& range = loadFileInfo.get<dirfilter>().equal_range(21);
    std::copy(range.first, range.second,
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList Sequencing" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "[ S  P  C  D]" << std::endl;
    for (auto it = loadFileInfo.get<composite>().cbegin();
        it != loadFileInfo.get<composite>().cend();) {
        std::stringstream ss;
        ss << "run->nSetupCmd[" << it->getSetupCmd() << "]" << std::endl;
        // find next range with current nSetupCmd & nPutFileCmd (cleanup ignored 
        // as should be identical for each SetupCmd/nPutFileCmd combination)
        const auto& spcRange = loadFileInfo.get<composite>().equal_range(
            boost::make_tuple(it->getSetupCmd(), it->getPutFileCmd()/*, it->getCleanupCmd()*/));
        // print out all LoadablePairs with equal nSetupCmd, nPutFileCmd
        std::copy(spcRange.first, spcRange.second,
            std::ostream_iterator<MLLEntry>(ss, "\n"));
        ss << "run->nCleanupCmd[" << it->getCleanupCmd() << "]" << std::endl;
        std::cout << ss.str();
        // advance the iterator to the next group of nSetupCmds
        it = spcRange.second;
    }

    IndexedFileInfo updateFileInfo;
    // test the copy constructor - requires element copy constructor also
    updateFileInfo = loadFileInfo;

    if (loadFileInfo==updateFileInfo) {
        std::cout << "loadFileInfo==updateFileInfo after copying..." << std::endl;
    }
        
    std::map<SyncAttr, IndexedFileInfo> fileInfo;
    
    IndexedFileInfo insyncFileInfo;
    std::copy(loadFileInfo.get<dirfilter>().lower_bound(22), 
        loadFileInfo.get<dirfilter>().upper_bound(23), 
            std::inserter(insyncFileInfo, insyncFileInfo.end()));
    
    fileInfo[SyncAttr::LOAD] = loadFileInfo;
    fileInfo[SyncAttr::UPDATE] = updateFileInfo;
    fileInfo[SyncAttr::INSYNC] = insyncFileInfo;
    
    for (const auto& next : fileInfo) {
        std::cout << next.first.getStringVal() << std::endl;
        std::cout << std::string(next.first.getStringVal().length(), '=') << std::endl;
        std::copy(next.second.cbegin(), next.second.cend(),
            std::ostream_iterator<MLLEntry>(std::cout, "\n"));
    }
    return 0;
}
