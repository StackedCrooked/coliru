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
class MLLEntry {
public:
    // typedef of local, module entries
    using StringPair = std::pair<std::string, std::string>;

    explicit MLLEntry(
        const StringPair& rStringPair,
        const int32_t& rValueA, 
        const int32_t& rValueB, 
        const int32_t& rValueC)
        : mStringPair(rStringPair)
        , mValueA(rValueA)
        , mValueB(rValueB)
        , mValueC(rValueC)
    {}

    // copy constructor
    MLLEntry(const MLLEntry& rhs)
        : mStringPair(rhs.mStringPair)
        , mValueA(rhs.mValueA)
        , mValueB(rhs.mValueB)
        , mValueC(rhs.mValueC)
    {}

    // move constructor
    MLLEntry(MLLEntry&& rhs)
        : mStringPair(std::move(rhs.mStringPair))
        , mValueA(std::move(rhs.mValueA))
        , mValueB(std::move(rhs.mValueB))
        , mValueC(std::move(rhs.mValueC))
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
        swap(mStringPair, rhs.mStringPair);
        swap(mValueA, rhs.mValueA);
        swap(mValueB, rhs.mValueB);
        swap(mValueC, rhs.mValueC);
    }

    // destructor
    virtual ~MLLEntry() = default;

    // ordering operator
    inline bool operator<(const MLLEntry& rhs) const {
        // operator<() -> string pairs ->  mValueA -> mValueB -> mValueC
        return std::tie(mStringPair, mValueA, mValueB,  mValueC) <
            std::tie(rhs.mStringPair, rhs.mValueA, rhs.mValueB, rhs.mValueC );
    }

    // ordering operator
    inline bool operator==(const MLLEntry& rhs) const {
        // operator==() -> string pairs ->  mValueA -> mValueB -> mValueC
        return std::tie(mStringPair, mValueA, mValueB, mValueC) <
            std::tie(rhs.mStringPair, rhs.mValueA, rhs.mValueB, rhs.mValueC);
    }

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] MLLEntry to send to the output stream.
     *
     * @return a reference to the updated stream
     */
    friend std::ostream& operator<<(
        std::ostream& os, const MLLEntry& rhs) {
        os << "["
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getValueA() << ","     // mValueA
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getValueB() << ","     // mValueB
            << std::setw(2) << std::setfill('0') << std::dec << std::right
            << rhs.getValueC() << "] ["   // mValueC
            << rhs.mStringPair.first << "->"
            << rhs.mStringPair.second << "]";
        return os;
    }

    // mValueA getter
    inline int32_t getValueA() const {
        return mValueA;
    }

    // mValueB getter
    inline int32_t getValueB() const {
        return mValueB;
    }

    // mValueC getter
    inline int32_t getValueC() const {
        return mValueC;
    }

    // first string
    inline const std::string& getString1() const {
        return mStringPair.first;
    }

    // second string
    inline const std::string& getString2() const {
        return mStringPair.second;
    }

private:
    StringPair mStringPair;
    int32_t mValueA;
    int32_t mValueB;
    int32_t mValueC;
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
        // composite key ordered using nSetupCmd->nFilePutCmd->MLLEntry
        // NOTE THAT THE FOLLOWING ordered_non_unique breaks set operations
        // as non uniqueness emulates multi-sets which is not what we want
        //, boost::multi_index::ordered_non_unique<boost::multi_index::tag<composite>
        , boost::multi_index::ordered_unique<boost::multi_index::tag<composite>
            , boost::multi_index::composite_key <
                MLLEntry
                , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getValueA>
                , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getValueB>
                , boost::multi_index::identity< MLLEntry >
            >
        >
        // sort by less<int> on mDirFilter (and also MLLEntry for uniqueness)
        , boost::multi_index::ordered_unique<boost::multi_index::tag<dirfilter>
            , boost::multi_index::composite_key <
                MLLEntry
                , boost::multi_index::const_mem_fun<MLLEntry, int32_t, &MLLEntry::getValueC>
                , boost::multi_index::identity< MLLEntry >
            >
        >
    >
>;


int main()
{
    // this is the sort of behavior I need where I can specify multiple indexes
    std::vector<MLLEntry::StringPair> fileInfo_01_05_10 = {
        MLLEntry::StringPair("xxx.txt", "xxx.txt"),
        MLLEntry::StringPair("yyy.txt", "yyy.txt")
    };

    // different setup/cleanup(02/11) identical put(05)
    std::vector<MLLEntry::StringPair> fileInfo_02_05_11 = {
        MLLEntry::StringPair("xxx.txt", "xxx.txt"),
        MLLEntry::StringPair("abc.txt", "abc.txt"),
        MLLEntry::StringPair("def.txt", "def.txt")
    };

    // completely different quartet
    std::vector<MLLEntry::StringPair> fileInfo_03_06_12 = {
        MLLEntry::StringPair("ghi.txt", "ghi.txt"),
        MLLEntry::StringPair("jkl.txt", "jkl.txt")
    };

    // identical setup/cleanup (03/12), different put(07)
    std::vector<MLLEntry::StringPair> fileInfo_03_07_12 = {
        MLLEntry::StringPair("001.txt", "001.txt"),
        MLLEntry::StringPair("002.txt", "002.txt"),
        MLLEntry::StringPair("003.txt", "003.txt")
    };

    // identical setup/cleanup (03/12), different put(08)
    std::vector<MLLEntry::StringPair> fileInfo_03_08_12 = {
        MLLEntry::StringPair("004.txt", "004.txt"),
        MLLEntry::StringPair("005.txt", "005.txt"),
        MLLEntry::StringPair("006.txt", "006.txt")
    };

    std::cout << "IndexedFileInfo inserting entries" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ 1  2  3]" << std::endl;
    IndexedFileInfo indexedFileInfo;
    // emplace construct MLLEntries
    for (const auto& next : fileInfo_01_05_10) {
        const auto& res = indexedFileInfo.insert(MLLEntry(next, 1, 5, 10));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_02_05_11) {
        const auto& res = indexedFileInfo.insert(MLLEntry(next, 2, 5, 11));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_03_06_12) {
        const auto& res = indexedFileInfo.insert(MLLEntry(next, 3, 3, 12));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    for (const auto& next : fileInfo_03_08_12) {
        const auto& res = indexedFileInfo.insert(MLLEntry(next, 3, 8, 12));
        if (res.second) {
            std::cout << *res.first << std::endl;
        } else {
            std::cout << *res.first << " - duplicate, not inserted" << std::endl;
        }
    }
    // duplicate entries should be rejected due to the 
    // unique identity key in the IndexedFileInfo
    for (const auto& next : fileInfo_03_08_12) {
        const auto& res = indexedFileInfo.insert(MLLEntry(next, 3, 8, 12));
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
    std::cout << "[ A  B  C]" << std::endl;
    std::copy(indexedFileInfo.cbegin(), indexedFileInfo.cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "IndexedFileInfo by DIR_FILTER" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "[ A  B  C]" << std::endl;
    std::copy(indexedFileInfo.get<dirfilter>().cbegin(),
        indexedFileInfo.get<dirfilter>().cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList - composite key order" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "[ A  B  C]" << std::endl;
    std::copy(indexedFileInfo.get<composite>().cbegin(),
        indexedFileInfo.get<composite>().cend(),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList (C >= 22)" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "[ A  B  C]" << std::endl;
    std::copy(indexedFileInfo.get<dirfilter>().lower_bound(22),
        indexedFileInfo.get<dirfilter>().cend(), 
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    // this range should return fileInfo1224 & fileInfo3125
    std::cout << "ModuleLoadList (lb22<->ub23)" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "[ A  B  C]" << std::endl;
    std::copy(indexedFileInfo.get<dirfilter>().lower_bound(22),
        indexedFileInfo.get<dirfilter>().upper_bound(23),
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList (Value3 == 21)" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "[ A  B  C]" << std::endl;
    const auto& range = indexedFileInfo.get<dirfilter>().equal_range(21);
    std::copy(range.first, range.second,
        std::ostream_iterator<MLLEntry>(std::cout, "\n"));

    std::cout << "ModuleLoadList Sequencing" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "[ A  B  C]" << std::endl;
    for (auto it = indexedFileInfo.get<composite>().cbegin();
        it != indexedFileInfo.get<composite>().cend();) {
        std::stringstream ss;
        ss << "run->mValue1[" << it->getValueA() << "]" << std::endl;
        // find next range with current nSetupCmd & nPutFileCmd (cleanup ignored 
        // as should be identical for each SetupCmd/nPutFileCmd combination)
        const auto& spcRange = indexedFileInfo.get<composite>().equal_range(
            boost::make_tuple(it->getValueA(), it->getValueB()/*, it->getCleanupCmd()*/));
        // print out all LoadablePairs with equal nSetupCmd, nPutFileCmd
        std::copy(spcRange.first, spcRange.second,
            std::ostream_iterator<MLLEntry>(ss, "\n"));
        ss << "run->mValue2[" << it->getValueB() << "]" << std::endl;
        std::cout << ss.str();
        // advance the iterator to the next group of nSetupCmds
        it = spcRange.second;
    }
}

