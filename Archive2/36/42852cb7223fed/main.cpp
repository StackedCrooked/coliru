#include <map>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include <functional>
#include <boost/optional.hpp>

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
        , mSequenceNum(std::move(rhs.mSequenceNum)) {
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
        const auto seqNum = mSequenceNum ? mSequenceNum.get() : 0;
        const auto rhsSeqNum = rhs.mSequenceNum ? rhs.mSequenceNum.get() : 0;
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        return std::tie(mChannel, prtyChar, seqNum) <
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
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
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        return std::tie(mChannel, prtyChar, seqNum) <
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
        return std::tie(mChannel, prtyChar, seqNum) >
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
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
    inline friend std::ostream& operator<<(
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

/**
 * Thread parameters used for configuration checking
 */
class SLDBConfigParams {
public:
    /**
     * Constructor<p>
     *
     * @param rDRFileName
     *                  [in] 'DR/XR' filename + extension
     * @param rModuleName
     *                  [in] module name - equivalent from a
     *                  uniqueness perspective to an IP address
     * @param rPriority [in] SLDB Priority object with strict weak
     *                  ordering priorities according to the
     *                  requirements
     */
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

    // operator used for ordering in a priority queue - do not include 
    // the 'DR/XR' here as equal_range will return less items
    inline bool operator<(const SLDBConfigParams& rhs) const {
        // compare priority levels - using tuple compare
        return std::tie(mPriority, mModuleName) <
            std::tie(rhs.mPriority, rhs.mModuleName);
    }

    // operator used for ordering in a priority queue - do not include 
    // the 'DR/XR' here as equal_range will return less items
    inline bool operator>(const SLDBConfigParams& rhs) const {
        // compare priority levels - using tuple compare
        return std::tie(mPriority, mModuleName) >
            std::tie(rhs.mPriority, rhs.mModuleName);
    }

    // equality operator used for std::adjacent_find 
    inline bool operator==(const SLDBConfigParams& rhs) const {
        if (this != &rhs) {
            return std::tie(mPriority, mModuleName) ==
                std::tie(rhs.mPriority, rhs.mModuleName);
        } else {
            return true;
        }
    }

    // priority level getter
    inline PriorityLevel getPriorityLevel() const {
        return mPriority;
    }

    // channel getter
    inline int32_t getChannel() const {
        return mPriority.getChannel();
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
* Top down tree structure representing all channel szPriority
* threads.<p>
*
* Each priority tree struct contains a vector of concurrent
* priorities that can be scheduled to run in the thread pool -
* note that the thread pool must have no entries associated
* with the current channel running before enqueueing these
* tasks. The application must wait for the thread pool to
* complete these tasks before queuing up the dependent tasks
* described in the mNext smart pointer. If the mNext is
* unassigned (nullptr) then we have reached the end of the
* tree.
*/
struct PriorityTree {
    explicit PriorityTree(
        const std::vector<SLDBConfigParams>& rConcurrent,
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
    inline friend std::ostream& operator<<(
        std::ostream& os, const PriorityTree& rhs)
    {
        // indent 2 spaces per depth level
        std::string indent = rhs.mDepth > 0 ? (std::string("+") +
            std::string((rhs.mDepth * 2) - 1, '-')) : std::string();
        // print out the concurrent threads that
        // can be scheduled with the thread pool
        for (const auto& next : rhs.mConcurrent){
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
    std::vector<SLDBConfigParams> mConcurrent;

    // recursion depth
    size_t mDepth;

    // these are concurrent threads that must be AFTER all
    // mConcurrent tasks have completed (exiting the thread pool)
    std::shared_ptr<PriorityTree> mNext;
};

int main()
{
    // test case taken from DLF log that 
    // requires module thread conflicts:
    //
    // channel[6] task tree
    // ====================
    // module[nic1], prty[6A], [INAVDATAHI_16M._xr]
    // module[nic1], prty[6A], [envmoddir._dr]
    // module[nic1], prty[6A], [jeppall._dr]
    // module[nic1], prty[6A], [tfsdir._dr]
    // module[nic1], prty[6A], [threatdir._dr]
    // --->module[proc1], prty[6B1], [INAVDATAHI_16M._xr]
    // --->module[proc1], prty[6B1], [envmoddir._dr]
    // --->module[proc1], prty[6B1], [jeppall._dr]
    // --->module[proc1], prty[6B1], [tfsdir._dr]
    // --->module[proc1], prty[6B1], [threatdir._dr]
    // --->module[aiopa1], prty[6B2], [INAVDATAHI_16M._xr]
    // --->module[aiopa1], prty[6B2], [jeppall._dr]
    // --->module[aiopa1], prty[6B2], [tfsdir._dr]
    // --->module[aiopa1], prty[6B2], [threatdir._dr]

    // more realistic priorities - C++11 brace initialization syntax
    std::vector<SLDBConfigParams> parameterInfo = {
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic1", PriorityLevel(6, 'A')),
        SLDBConfigParams("envmoddir._dr", "nic1", PriorityLevel(6, 'A')),
        SLDBConfigParams("jeppall._dr", "nic1", PriorityLevel(6, 'A')),
        SLDBConfigParams("tfsdir._dr", "nic1", PriorityLevel(6, 'A')),
        SLDBConfigParams("threatdir._dr", "nic1", PriorityLevel(6, 'A')),

        SLDBConfigParams("INAVDATAHI_16M._xr", "proc1", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("envmoddir._dr", "proc1", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "proc1", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("tfsdir._dr", "proc1", PriorityLevel(6, 'B', 1)),

        // the following 4 should be schedulable together 
        // as they run on different procs
        SLDBConfigParams("threatdir._dr", "proc1", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("threatdir._dr", "proc2", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("threatdir._dr", "proc3", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("threatdir._dr", "proc4", PriorityLevel(6, 'B', 1)),

        SLDBConfigParams("INAVDATAHI_16M._xr", "aiopa1", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "aiopa1", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("tfsdir._dr", "aiopa1", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("threatdir._dr", "aiopa1", PriorityLevel(6, 'B', 2)),
    };

    std::cout << "SLDBConfigParams - unordered" << std::endl;
    std::cout << "============================" << std::endl;
    std::copy(parameterInfo.begin(), parameterInfo.end(),
        std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
    std::cout << std::endl;

    // order the parameters in (highest to lowest priority).
    std::sort(parameterInfo.begin(), parameterInfo.end(), std::greater<SLDBConfigParams>());
    std::cout << "SLDBConfigParams - channel->priority order" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::copy(parameterInfo.begin(), parameterInfo.end(),
        std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
    std::cout << std::endl;

    // channel only comparator - don't care about the order of the other fields
    // although within this range they will be ordered using priorityParamPred
    static const auto gChannelPred = [](
        const SLDBConfigParams& lhs, 
        const SLDBConfigParams& rhs)->bool {
        return lhs.getPriorityLevel().mChannel < 
            rhs.getPriorityLevel().mChannel;
    };

    static const auto gPriorityLevelPred = [](
        const SLDBConfigParams& lhs,
        const SLDBConfigParams& rhs)->bool {
        return lhs.getPriorityLevel() <
            rhs.getPriorityLevel();
    };

    // parameters organized per channel and sorted using priorities within each channel
    std::map<int32_t, std::shared_ptr<PriorityTree>> channelPriorityInfo;

    // iterate over each of the channel ranges
    for (auto iter = parameterInfo.begin(); iter != parameterInfo.end();){
        // get the next group of channel parameters
        auto chRange = std::equal_range(iter, parameterInfo.end(), *iter, gChannelPred);
        std::vector<SLDBConfigParams> chParams(chRange.first, chRange.second);

        // order the parameters in (highest to lowest priority).
        std::sort(chParams.begin(), chParams.end());
        std::cout << "channel [" << iter->getChannel()
            << "] ordered priorities" << std::endl;
        std::cout << "==============================" << std::endl;
        std::copy(chParams.begin(), chParams.end(),
            std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
        std::cout << std::endl;

        size_t depth = 0;
        std::shared_ptr<PriorityTree> priorityTree, priorityTreeRoot;
        for (auto iter1 = chParams.begin(); iter1 != chParams.end();) {
            // matching priories using gPriorityPred to find matches
            // the orderedParams must also be ordered using this predicate
            const auto& range = std::equal_range(iter1, 
                chParams.end(), *iter1, gPriorityLevelPred);
            std::copy(range.first, range.second,
                std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
            std::cout << std::endl;
            // find identical priorities
            auto defIter = range.first;
            while (defIter != range.second) {
                std::vector<SLDBConfigParams> concurrent;
                // use equality comparator SLDBConfigParams::operator==()
                auto tempIter = std::adjacent_find(defIter, range.second);
                // check for boundary condition
                if (tempIter != range.second) {
                    std::copy(defIter, tempIter + 1, std::back_inserter(concurrent));
                    // build the tree here
                    if (!priorityTree) {
                        priorityTree = std::make_shared<PriorityTree>(concurrent, depth++);
                        if (!priorityTreeRoot) {
                            priorityTreeRoot = priorityTree;
                        }
                    } else {
                        priorityTree->mNext = std::make_shared<
                            PriorityTree>(concurrent, depth++);
                        priorityTree = priorityTree->mNext;
                    }
                    defIter = tempIter + 1;
                } else {
                    std::copy(defIter, range.second, 
                        std::back_inserter(concurrent));
                    // build the tree here
                    if (!priorityTree) {
                        priorityTree = std::make_shared<
                            PriorityTree>(concurrent, depth++);
                        if (!priorityTreeRoot) {
                            priorityTreeRoot = priorityTree;
                        }
                    } else {
                        priorityTree->mNext = std::make_shared<
                            PriorityTree>(concurrent, depth++);
                        priorityTree = priorityTree->mNext;
                    }
                    defIter = tempIter;
                }
                concurrent.clear();
            }
            iter1 = range.second;
        }
        channelPriorityInfo[iter->getChannel()] = priorityTreeRoot;
        std::cout << *priorityTreeRoot << std::endl;
        iter = chRange.second;
    }
}
