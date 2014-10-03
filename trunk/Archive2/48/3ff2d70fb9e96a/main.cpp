#include <map>
#include <string>
#include <cstdint>
#include <memory>
#include <sstream>
#include <iostream>
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
        const std::string& rFilename = std::string(),
        const boost::optional<int32_t>& rSequenceNum =
            boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar)
        , mFilename(rFilename)
        , mSequenceNum(rSequenceNum)
    {}

    // copy constructor
    PriorityLevel(const PriorityLevel& rhs)
        : mChannel(rhs.mChannel)
        , mPriorityChar(rhs.mPriorityChar)
        , mFilename(rhs.mFilename)
        , mSequenceNum(rhs.mSequenceNum)
    {}

    // move constructor
    PriorityLevel(PriorityLevel&& rhs)
        : mChannel(std::move(rhs.mChannel))
        , mPriorityChar(std::move(rhs.mPriorityChar))
        , mFilename(std::move(rhs.mFilename))
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
        swap(mFilename, rhs.mFilename);
        swap(mSequenceNum, rhs.mSequenceNum);
    }

    // non-throwing copy-and-swap idiom unified assignment
    PriorityLevel& operator=(PriorityLevel rhs) {
        rhs.swap(*this);
        return *this;
    }

    // equality operator
    inline bool operator==(const PriorityLevel& rhs) const {
        return std::tie(mChannel, mPriorityChar, mFilename, mSequenceNum) ==
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mFilename, rhs.mSequenceNum);
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
        return std::tie(mChannel, mPriorityChar, mFilename, seqNum) >
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mFilename, rhsSeqNum);
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
        return std::tie(mChannel, mPriorityChar, mFilename, seqNum) <
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mFilename, rhsSeqNum);
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

    // priority char getter
    inline char getPriorityChar() const {
        return mPriorityChar;
    }

    // filename getter
    inline std::string getFilename() const {
        return mFilename;
    }

    // string representation of the priority string
    inline std::string getPriorityStr(const bool bShowFilename = false) const {
        std::stringstream ss;
        ss << mChannel << mPriorityChar;
        if (mSequenceNum) {
            ss << mSequenceNum.get();
        }
        if (bShowFilename) {
            // print the filename to the right
            ss << "[" << mFilename << "]";
        }
        return ss.str();
    }
private:
    // channel number - top level order field
    int32_t mChannel;
    // single upper case character A=>'highest priority'
    char mPriorityChar;
    // '_dr/_xr' filename+ext associated with this priority thread
    std::string mFilename;
public:
    // optional field - when present indicates start order
    boost::optional<int32_t> mSequenceNum;
};

/**
 * Branch representing fundamental building block of
 * a priority tree containing szPriority entries.<p>
 *
 * Each priority tree struct contains a vector of concurrent
 * priorities that can be scheduled to run in the thread pool -
 * note that the thread pool must have no entries associated
 * with the current channel running before enqueueing these
 * tasks. The application must wait for the thread pool to
 * complete these tasks before queuing up the dependent tasks
 * described in the mNextNode smart pointer. If mNextNode is
 * unassigned (nullptr), then we have reached the end of the
 * tree.
 */
template <typename T/*, typename Param*/>
struct PriorityNode {
    explicit PriorityNode(
        const std::vector<T/*std::pair<T, Param>*/>& rConcurrent,
        const std::shared_ptr<PriorityNode<T/*, Param*/>>& rNext = 
            std::shared_ptr<PriorityNode<T/*, Param*/>>(),
        const size_t& rDepth = 0)
        : mConcurrent(rConcurrent)
        , mNextNode(rNext)
        , mDepth(rDepth)
        , mDone(false)
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
        std::ostream& os, const PriorityNode<T/*, Param*/>& rhs) {
        // indent 2 spaces per depth level
        std::string indent = rhs.mDepth > 0 ?
            (std::string("|") +
            std::string((rhs.mDepth * 2) - 1, '_')) :
            std::string();
        // print out the concurrent threads that 
        // can be scheduled with the thread pool
        for (const auto& next : rhs.mConcurrent) {
            os << indent << next << std::endl;
        }
        // print the dependent priorities that can only
        // be scheduled when the concurrent ones are finished
        if (rhs.mNextNode) {
            os << *rhs.mNextNode << std::endl;
        }
        return os;
    }
    // these are all equivalent thread priorities
    // that can be run simultaneously
    std::vector<T/*std::pair<T, Param>*/> mConcurrent;

    // these are concurrent threads that must be AFTER all 
    // mConcurrent tasks have completed (exiting the thread pool)
    std::shared_ptr<PriorityNode<T/*, Param*/>> mNextNode;

    // recursion depth
    size_t mDepth;

    // flag indicating finished enqueueing all this node's mConcurrent tasks
    bool mDone;
};


int main()
{    
    // more realistic priorities - Dassault
    std::vector<PriorityLevel> gPriorities = {
        PriorityLevel(1, 'A', "[foo._dr]"),
        PriorityLevel(3, 'A', "[bar._dr]"),
        PriorityLevel(1, 'B', "[foo._dr]", 1),
        PriorityLevel(1, 'B', "[bar._dr]", 1),
        PriorityLevel(1, 'B', "[foo._dr]", 2),
        PriorityLevel(1, 'B', "[bar._dr]", 2),
        PriorityLevel(1, 'B', "[foo._dr]", 3),
        PriorityLevel(1, 'B', "[foo._dr]", 3),
        PriorityLevel(1, 'B', "[foo._dr]", 4),
        PriorityLevel(1, 'B', "[foo._dr]", 5),
        PriorityLevel(1, 'C', "[foo._dr]", 1), // test
        PriorityLevel(1, 'C', "[foo._dr]", 2), // test
        PriorityLevel(1, 'A', "[foo._dr]", 1), // test
        PriorityLevel(2, 'A', "[foo._dr]"),
        PriorityLevel(2, 'B', "[foo._dr]", 1),
        PriorityLevel(2, 'B', "[foo._dr]", 2),
        PriorityLevel(2, 'B', "[foo._dr]", 3),
        PriorityLevel(2, 'B', "[foo._dr]", 2)
    };
    
    std::map<int32_t, std::shared_ptr<PriorityNode<PriorityLevel/*, int*/>>> priorityInfo;

    return 1;
}