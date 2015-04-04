#include <map>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include <functional>
#include <boost/optional.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


/**
 *  represents the szPriorityLevel<p>
 *
 * the szPriority Field contains a channel, priority character
 * [A-Z] (from highest priority to -lowest priority)
 * and an optional sequence number.
 */
class PriorityLevel {
public:
    // default constructor
    PriorityLevel(
        const int32_t& rChannel = -1,
        const char priorityChar = 'Z',
        const boost::optional<int32_t>& rSequenceNum =
            boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar)
        , mSequenceNum(rSequenceNum)
    {}

    // copy constructor
    PriorityLevel(const PriorityLevel& rhs)
        : mChannel(rhs.mChannel)
        , mPriorityChar(rhs.mPriorityChar)
        , mSequenceNum(rhs.mSequenceNum)
    {}

    // move constructor
    PriorityLevel(PriorityLevel&& rhs)
        : mChannel(std::move(rhs.mChannel))
        , mPriorityChar(std::move(rhs.mPriorityChar))
        , mSequenceNum(std::move(rhs.mSequenceNum))
    {
        // reset optionals - not really necessary
        rhs.mSequenceNum = boost::none;
    }

    // non-throwing-swap idiom
    inline void swap(PriorityLevel& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // no need to swap base members - as we are topmost class
        swap(mChannel, rhs.mChannel);
        swap(mPriorityChar, rhs.mPriorityChar);
        swap(mSequenceNum, rhs.mSequenceNum);
    }

    // non-throwing copy-and-swap idiom unified assignment
    PriorityLevel& operator=(PriorityLevel rhs) {
        rhs.swap(*this);
        return *this;
    }

    // equality operator
    inline bool operator==(const PriorityLevel& rhs) const {
        return std::tie(mChannel, mPriorityChar, mSequenceNum) ==
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mSequenceNum);
    }

    // inequality operator opposite to equality operator
    inline bool operator!=(const PriorityLevel& rhs) const {
        return !(operator==(rhs));
    }

    /**
     * comparator that orders the elements in the
     * priority_queue<p>
     *
     * Implemented via a lexicographical comparison using
     * std::tuple<T...> as a helper. Tuple comparison works as
     * follows: compares the first elements, if they are equivalent,
     * compares the second elements, if those are equivalent,
     * compares the third elements, and so on. All comparison
     * operators are short - circuited; they do not access tuple
     * elements beyond what is necessary to determine the result of
     * the comparison. note that the presence of the sequence number
     * assigns a lower priority (bigger value 1) contribution to the
     * lexicographical nature of the comparison
     *
     * @param rhs    [in] PriorityLevel to compare against
     *
     * @return 'true' if this has lower priority than rhs
     */
    inline bool operator<(const PriorityLevel& rhs) const {
        auto seqNum = mSequenceNum ? mSequenceNum.get() : 0;
        auto rhsSeqNum = rhs.mSequenceNum ? rhs.mSequenceNum.get() : 0;
        return std::tie(mChannel, mPriorityChar, seqNum) >
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhsSeqNum);
    }

    // operator>=() is opposite to operator<()
    inline bool operator>=(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
    }

    // operator>() implemented so that it now works with std::sort()
    // preserving the strict weak ordering mathematical rules
    inline bool operator>(const PriorityLevel& rhs) const {
        auto seqNum = mSequenceNum ? mSequenceNum.get() : 0;
        auto rhsSeqNum = rhs.mSequenceNum ? rhs.mSequenceNum.get() : 0;
        return std::tie(mChannel, mPriorityChar, seqNum) <
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhsSeqNum);
    }

    // operator<=() is opposite to operator>()
    inline bool operator<=(const PriorityLevel& rhs) const {
        return !(operator>(rhs));
    }

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] PriorityLevel to send to the output
     *               stream.
     *
     * @return a reference to the updated stream
     */
    inline friend std::ostream& operator << (
        std::ostream& os, const PriorityLevel& rhs) {
        os << rhs.getPriorityStr();
        return os;
    }

    // channel getter
    inline int32_t getChannel() const {
        return mChannel;
    }

    // string representation of the priority string
    inline std::string getPriorityStr() const {
        std::stringstream ss;
        ss << mChannel << mPriorityChar;
        if (mSequenceNum) {
            ss << mSequenceNum.get();
        }
        return ss.str();
    }

    // channel number - top level order field
    int32_t mChannel;
    // single upper case character A=>'highest priority'
    char mPriorityChar;
    // optional field - when present indicates start order
    boost::optional<int32_t> mSequenceNum;
};

/** Thread parameters used for configuration checking */
class SLDBConfigParams {
public:
    explicit SLDBConfigParams(
        const std::string& rDRFileName = std::string(),
        const std::string& rModuleName = std::string(),
        const PriorityLevel& rPriority = PriorityLevel())
        : mDRFileName(rDRFileName)
        , mModuleName(rModuleName)
        , mPriority(rPriority)
    {}

    // copy constructor
    SLDBConfigParams(const SLDBConfigParams& rhs)
        : mDRFileName(rhs.mDRFileName)
        , mModuleName(rhs.mModuleName)
        , mPriority(rhs.mPriority)
    {}

    // move constructor
    SLDBConfigParams(SLDBConfigParams&& rhs)
        : mDRFileName(std::move(rhs.mDRFileName))
        , mModuleName(std::move(rhs.mModuleName))
        , mPriority(std::move(rhs.mPriority))
    {}

    // non-throwing copy-and-swap idiom unified assignment
    inline SLDBConfigParams& operator=(SLDBConfigParams rhs) {
        rhs.swap(*this);
        return *this;
    }

    // non-throwing-swap idiom
    inline void swap(SLDBConfigParams& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // swap base members
        //Base::swap(rhs);
        // swap members here
        swap(mDRFileName, rhs.mDRFileName);
        swap(mModuleName, rhs.mModuleName);
        swap(mPriority, rhs.mPriority);
    }

    // destructor
    virtual ~SLDBConfigParams() = default;

    // operator used for ordering in a priority queue
    inline bool operator<(const SLDBConfigParams& rhs) const {
        // compare priority levels - using tuple compare
        return std::tie(mPriority, mModuleName, mDRFileName) < 
            std::tie(rhs.mPriority, rhs.mModuleName, rhs.mDRFileName);
    }

    // equality operator
    inline bool operator==(const SLDBConfigParams& rhs) const {
        if (this != &rhs) {
            return std::tie(mPriority, mModuleName, mDRFileName) == 
                std::tie(rhs.mPriority, rhs.mModuleName, rhs.mDRFileName);
        } else {
            return true;
        }
    }

    // priority level getter
    inline PriorityLevel getPriorityLevel() const {
        return mPriority;
    }

    // mModuleName getter
    inline std::string getModuleName() const {
        return mModuleName;
    }

    // mFileName  getter
    inline std::string getDRFilename() const {
        return mDRFileName;
    }

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] SLDBConfigParams to send to the output
     *               stream.
     *
     * @return a reference to the updated stream
     */
    friend std::ostream& operator<<(
        std::ostream& os, const SLDBConfigParams& rhs) {
        os << "module[" << rhs.mModuleName
            << "], prty[" << rhs.mPriority
            << "], dr/xr[" << rhs.mDRFileName
            << "]";
        return os;
    }

    // 'DR/XR' file
    std::string mDRFileName;

    // module name
    std::string mModuleName;

    // channel priority level
    PriorityLevel mPriority;
};


/**
 * Top down tree structure representiing all channel szPriority
 * threads.<p>
 * 
 * Each priority tree struct contains a vector of concurrent
 * priorities that can be scheduled to run in the thread pool -
 * note that the thread pool must have no entries associated
 * with the current channel running efore enqueueing these
 * tasks. The application must wait for the thread pool to
 * complete these tasks before queueing up the dependent tasks
 * described in the mNext smart pointer. If the mNext is 
 * unassigned (nullptr) then we have reached the end of the 
 * tree. 
 */
struct PriorityTree {
    explicit PriorityTree(
        const std::vector<PriorityLevel>& rConcurrent, 
        const size_t& rDepth = 0)
        : mConcurrent(rConcurrent)
        , mDepth(rDepth)
        , mNext()
    {}

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] PriorityLevel to send to the output
     *               stream.
     *
     * @return a reference to the updated stream
     */
    inline friend std::ostream& operator << (
        std::ostream& os, const PriorityTree& rhs) {
        // indent 2 spaces per depth level
        std::string indent = rhs.mDepth > 0 ? 
            (std::string("+") + std::string((rhs.mDepth * 2) - 1, '-')) : 
            std::string();
        // print out the concurrent threads that 
        // can be scheduled with the thread pool
        for (const auto& next : rhs.mConcurrent) {
            os << indent << next << std::endl;
        }
        // print the dependent priorities that can only
        // be scheduled when the concurrent ones are finished
        if (rhs.mNext) {
            os << *rhs.mNext << std::endl;
        }
        return os;
    }
    // these are all equivalent thread priorities
    // that can be run simultaneously
    std::vector<PriorityLevel> mConcurrent;

    // recursion depth
    size_t mDepth;

    // these are concurrent threads that must be AFTER all 
    // mConcurrent tasks have completed (exiting the thread pool)
    std::shared_ptr<PriorityTree> mNext;
};

int main()
{    
    // more realistic priorities - Dassault
    std::vector<PriorityLevel> gPriorities = {
        PriorityLevel(1, 'A'),
        PriorityLevel(3, 'A'),
        PriorityLevel(1, 'B', 1),
        PriorityLevel(1, 'B', 1),
        PriorityLevel(1, 'B', 2),
        PriorityLevel(1, 'B', 2),
        PriorityLevel(1, 'B', 3),
        PriorityLevel(1, 'B', 3),
        PriorityLevel(1, 'B', 4),
        PriorityLevel(1, 'B', 5),
        PriorityLevel(1, 'C', 1), // test
        PriorityLevel(1, 'C', 2), // test
        PriorityLevel(1, 'A', 1), // test
        PriorityLevel(2, 'A'),
        PriorityLevel(2, 'B', 1),
        PriorityLevel(2, 'B', 2),
        PriorityLevel(2, 'B', 3),
        PriorityLevel(2, 'B', 2)
    };

    // channel only comparator - don't care about the order of the other fields
    const auto channelPred = [](const PriorityLevel& a, const PriorityLevel& b) {
        return a.getChannel() < b.getChannel();
    };

    // ignore the filename in the priority ordering - maybe add back later
    // as the last field to compare - not sure yet.
    const auto priorityPred = [](const PriorityLevel& a, const PriorityLevel& b) {
        // sequence number present is important not its value
        auto seqNumA = a.mSequenceNum ? /*a.mSequenceNum.get()*/1 : 0;
        auto seqNumB = b.mSequenceNum ? /*b.mSequenceNum.get()*/1 : 0;
        // no real need to include channel as all channels compared
        // using this comparator will have matching channels already
        // left in for completeness.
        return std::tie(a.mChannel, a.mPriorityChar, seqNumA) <
            std::tie(b.mChannel, b.mPriorityChar, seqNumB);
    };

    // order the PriorityLevels in descending order 
    // (highest to lowest priority). Note that higher priority
    // values use lower priority characters and sequence numbers
    // which is why the PriorityLevel operator> uses < comparisons
    // in the tuple fields
    std::sort(gPriorities.begin(), gPriorities.end(),
        std::greater<PriorityLevel>());
    std::cout << "priorities - ordered by channel" << std::endl;
    std::copy(gPriorities.begin(), gPriorities.end(),
        std::ostream_iterator<PriorityLevel>(
            std::cout, "\n"));
    std::cout << std::endl;

    std::map<int32_t, std::shared_ptr<PriorityTree>> channelPriorityInfo;
    // iterate over each of the channel ranges
    for (auto iter = gPriorities.begin(); iter != gPriorities.end();) {
        auto channelRange = std::equal_range(iter, gPriorities.end(), 
            iter->mChannel, channelPred);
#if 0            
        std::cout << "channel [" << iter->mChannel << "] priorities - unordered" << std::endl;
        std::copy(channelRange.first, channelRange.second,
            std::ostream_iterator<PriorityLevel>(
                std::cout, "\n"));
        std::cout << std::endl;
#endif
        // convert the channelRange into a sorted list of priorities
        std::vector<PriorityLevel> ch_ptys(channelRange.first, channelRange.second);
        std::sort(ch_ptys.begin(), ch_ptys.end(), priorityPred);
        // print the channel ordered priorities
        std::cout << "channel [" << iter->mChannel << "] priorities - ordered" << std::endl;
        std::copy(ch_ptys.begin(), ch_ptys.end(),
            std::ostream_iterator<PriorityLevel>(
                std::cout, "\n"));
        std::cout << std::endl;

        // iterate over sub ranges within the channel ordered priorities 
        auto prevRange = std::make_pair(ch_ptys.begin(), ch_ptys.begin());
        std::shared_ptr<PriorityTree> priorityTree, priorityTreeRoot;
        size_t depth = 0;
        for (auto iter1 = ch_ptys.begin(); iter1 != ch_ptys.end();) {
            auto range = std::equal_range(iter1, ch_ptys.end(), *iter1, priorityPred);
            // this represents all the equivalent priority levels
            auto concurrent = std::vector<PriorityLevel>(range.first, range.second);
#if 0            
            std::cout << "identical priorities" << std::endl;
            std::copy(range.first, range.second,
                std::ostream_iterator<PriorityLevel>(
                    std::cout, "\n"));
#endif                    
            std::cout << std::endl;
            // build the tree here
            if (!priorityTree) {
                priorityTree = std::make_shared<PriorityTree>(concurrent, depth++);
                if (!priorityTreeRoot) {
                    priorityTreeRoot = priorityTree;
                }
            } else {
                priorityTree->mNext = std::make_shared<PriorityTree>(concurrent, depth++);
                priorityTree = priorityTree->mNext;
            }
            prevRange = range;
            iter1 = range.second;
        }
        channelPriorityInfo[iter->mChannel] = priorityTreeRoot;
        std::cout << *priorityTreeRoot << std::endl;
        iter = channelRange.second;
    }   
}