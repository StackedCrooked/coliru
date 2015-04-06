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
    explicit PriorityLevel(
        const int32_t& rChannel = 0,
        const char priorityChar = 'Z',
        const boost::optional<int32_t>& rSequenceNum =
            boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar & ~(1<<5))
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
        // presence of sequence number => lower priority
        const auto seqNum = mSequenceNum ? /*mSequenceNum.get()*/0 : 1;
        const auto rhsSeqNum = rhs.mSequenceNum ? /*rhs.mSequenceNum.get()*/0 : 1;
        // @JC make sure mPriorityChar upper case
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        return std::tie(mChannel, prtyChar, seqNum) >
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
    }

    // operator>=() is opposite to operator<()
    inline bool operator>=(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
    }

    // operator>() implemented so that it now works with std::sort()
    // preserving the strict weak ordering mathematical rules
    inline bool operator>(const PriorityLevel& rhs) const {
        // presence of sequence number => lower priority
        auto seqNum = mSequenceNum ? /*mSequenceNum.get()*/ 0 : 1;
        auto rhsSeqNum = rhs.mSequenceNum ? /*rhs.mSequenceNum.get()*/ 0 : 1;
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        return std::tie(mChannel, prtyChar, seqNum) <
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
    //channel[1] task tree
    //====================
    //module[nic2], prty[1A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[nic2], prty[1A], dr/xr(s)[jeppall._dr]
    //--->module[agm4], prty[1B1], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[agm4], prty[1B1], dr/xr(s)[jeppall._dr]
    //--->module[proc2], prty[1B2], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[proc2], prty[1B2], dr/xr(s)[jeppall._dr]
    //--->module[gio1b], prty[1B3], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio1b], prty[1B3], dr/xr(s)[jeppall._dr]
    //--->module[gio2], prty[1B4], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio2], prty[1B4], dr/xr(s)[jeppall._dr]
    //
    //channel[2] task tree
    //====================
    //module[nic5], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[nic5], dr/xr(s)[jeppall._dr]
    //--->module[agm2], prty[2B1], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[agm2], prty[2B1], dr/xr(s)[jeppall._dr]
    //--->module[proc5], prty[2B2], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[proc5], prty[2B2], dr/xr(s)[jeppall._dr]
    //--->module[gio5], prty[2B3], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio5], prty[2B3], dr/xr(s)[jeppall._dr]
    //--->module[csio3], prty[2B4], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[csio3], prty[2B4], dr/xr(s)[jeppall._dr]
    //
    //channel[3] task tree
    //====================
    //module[nic6], prty[3A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[nic6], prty[3A], dr/xr(s)[jeppall._dr]
    //--->module[agm1], prty[3B1], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[agm1], prty[3B1], dr/xr(s)[jeppall._dr]
    //--->module[proc6], prty[3B2], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[proc6], prty[3B2], dr/xr(s)[jeppall._dr]
    //--->module[egpwm1], prty[3B3], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[egpwm1], prty[3B3], dr/xr(s)[jeppall._dr]
    //--->module[cio3], prty[3B4], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[cio3], prty[3B4], dr/xr(s)[jeppall._dr]
    //--->module[gio6], prty[3B5], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio6], prty[3B5], dr/xr(s)[jeppall._dr]
    //
    //channel[4] task tree
    //====================
    //module[rnic1], prty[4A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[rnic1], prty[4A], dr/xr(s)[jeppall._dr]
    //--->module[rproc1], prty[4B], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[rproc1], prty[4B], dr/xr(s)[jeppall._dr]
    //
    //channel[5] task tree
    //====================
    //module[rnic2], prty[5A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[rnic2], prty[5A], dr/xr(s)[jeppall._dr]
    //--->module[rproc2], prty[5B], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[rproc2], prty[5B], dr/xr(s)[jeppall._dr]
    //
    //channel[6] task tree
    //====================
    //module[nic1], prty[6A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[nic1], prty[6A], dr/xr(s)[jeppall._dr]
    //--->module[proc1], prty[6B1], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[proc1], prty[6B1], dr/xr(s)[jeppall._dr]
    //--->module[aiopa1], prty[6B2], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[aiopa1], prty[6B2], dr/xr(s)[jeppall._dr]
    //--->module[aiopb1], prty[6B3], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[aiopb1], prty[6B3], dr/xr(s)[jeppall._dr]
    //--->module[cio1], prty[6B4], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[cio1], prty[6B4], dr/xr(s)[jeppall._dr]
    //--->module[gio1a], prty[6B5], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio1a], prty[6B5], dr/xr(s)[jeppall._dr]
    //--->module[csio1], prty[6B6], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[csio1], prty[6B6], dr/xr(s)[jeppall._dr]
    //--->module[gio1], prty[6B7], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio1], prty[6B7], dr/xr(s)[jeppall._dr]
    //
    //channel[7] task tree
    //====================
    //module[nic3], prty[7A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[nic3], prty[7A], dr/xr(s)[jeppall._dr]
    //--->module[agm3], prty[7B1], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[agm3], prty[7B1], dr/xr(s)[jeppall._dr]
    //--->module[proc3], prty[7B2], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[proc3], prty[7B2], dr/xr(s)[jeppall._dr]
    //--->module[egpwm2], prty[7B3], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[egpwm2], prty[7B3], dr/xr(s)[jeppall._dr]
    //--->module[gio2a], prty[7B4], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio2a], prty[7B4], dr/xr(s)[jeppall._dr]
    //--->module[gio3], prty[7B6], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio3], prty[7B6], dr/xr(s)[jeppall._dr]
    //
    //channel[8] task tree
    //====================
    //module[nic4], prty[8A], dr/xr(s)[INAVDATAHI_16M._xr]
    //module[nic4], prty[8A], dr/xr(s)[jeppall._dr]
    //--->module[proc4], prty[8B1], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[proc4], prty[8B1], dr/xr(s)[jeppall._dr]
    //--->module[aiopa2], prty[8B2], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[aiopa2], prty[8B2], dr/xr(s)[jeppall._dr]
    //--->module[aiopb2], prty[8B3], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[aiopb2], prty[8B3], dr/xr(s)[jeppall._dr]
    //--->module[cio2], prty[8B4], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[cio2], prty[8B4], dr/xr(s)[jeppall._dr]
    //--->module[gio2b], prty[8B5], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio2b], prty[8B5], dr/xr(s)[jeppall._dr]
    //--->module[gio4], prty[8B6], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[gio4], prty[8B6], dr/xr(s)[jeppall._dr]
    //--->module[csio2], prty[8B7], dr/xr(s)[INAVDATAHI_16M._xr]
    //--->module[csio2], prty[8B7], dr/xr(s)[jeppall._dr]

    // more realistic priorities - C++11 brace initialization syntax
    std::vector<SLDBConfigParams> parameterInfo = {
        // channel[1] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic2", PriorityLevel(1, 'A')),
        SLDBConfigParams("jeppall._dr", "nic2", PriorityLevel(1, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm4", PriorityLevel(1, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm4", PriorityLevel(1, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc2", PriorityLevel(1, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc2", PriorityLevel(1, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio1b", PriorityLevel(1, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "gio1b", PriorityLevel(1, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio2", PriorityLevel(1, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio2", PriorityLevel(1, 'B', 4)),

        // channel[2] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic5", PriorityLevel(2, 'A')),
        SLDBConfigParams("jeppall._dr", "nic5", PriorityLevel(2, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm2", PriorityLevel(2, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm2", PriorityLevel(2, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc5", PriorityLevel(2, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc5", PriorityLevel(2, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio5", PriorityLevel(2, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "gio5", PriorityLevel(2, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "csio3", PriorityLevel(2, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "csio3", PriorityLevel(2, 'B', 4)),

        //channel[3] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic6", PriorityLevel(3, 'A')),
        SLDBConfigParams("jeppall._dr", "nic6", PriorityLevel(3, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm1", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm1", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc6", PriorityLevel(2, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc6", PriorityLevel(3, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "egpwm1", PriorityLevel(3, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "egpwm1", PriorityLevel(3, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "cio3", PriorityLevel(2, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "cio3", PriorityLevel(3, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio6", PriorityLevel(3, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio6", PriorityLevel(3, 'B', 4)),

        // channel[4] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "rnic1", PriorityLevel(4, 'A')),
        SLDBConfigParams("jeppall._dr", "rnic1", PriorityLevel(4, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "rproc1", PriorityLevel(4, 'B')),
        SLDBConfigParams("jeppall._dr", "rproc1", PriorityLevel(4, 'B')),

        // channel[5] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "rnic2", PriorityLevel(5, 'A')),
        SLDBConfigParams("jeppall._dr", "rnic2", PriorityLevel(5, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "rproc2", PriorityLevel(5, 'B')),
        SLDBConfigParams("jeppall._dr", "rproc2", PriorityLevel(5, 'B')),

        // channel[6] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic1", PriorityLevel(6, 'A')),
        SLDBConfigParams("jeppall._dr", "nic1", PriorityLevel(6, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc1", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "proc1", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "aiopa1", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "aiopa1", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "aiopb1", PriorityLevel(6, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "aiopb1", PriorityLevel(6, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "cio1", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "cio1", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio1a", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio1a", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "csio1", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "csio1", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio1", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio1", PriorityLevel(6, 'B', 4)),

        // channel[7] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic3", PriorityLevel(7, 'A')),
        SLDBConfigParams("jeppall._dr", "nic3", PriorityLevel(7, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm3", PriorityLevel(7, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm3", PriorityLevel(7, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc3", PriorityLevel(7, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc3", PriorityLevel(7, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "egpwm2", PriorityLevel(7, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "egpwm2", PriorityLevel(7, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio2a", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio2a", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio3", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio3", PriorityLevel(7, 'B', 4)),
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
#if 0
        std::cout << "channel [" << iter->getChannel()
            << "] ordered priorities" << std::endl;
        std::cout << "==============================" << std::endl;
        std::copy(chParams.begin(), chParams.end(),
            std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
        std::cout << std::endl;
#endif

        size_t depth = 0;
        std::shared_ptr<PriorityTree> priorityTree, priorityTreeRoot;
        for (auto iter1 = chParams.begin(); iter1 != chParams.end();) {
            // matching priories using gPriorityPred to find matches
            // the orderedParams must also be ordered using this predicate
            const auto& range = std::equal_range(iter1,
                chParams.end(), *iter1, gPriorityLevelPred);
#if 0
            std::copy(range.first, range.second,
                std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
            std::cout << std::endl;
#endif
            // find identical priorities
            auto defIter = range.first;
            while (defIter != range.second) {
                std::vector<SLDBConfigParams> concurrent;
                // use equality comparator 
                // SLDBConfigParams::operator==()
                auto tempIter = std::adjacent_find(
                    defIter, range.second);
                // check for boundary condition
                if (tempIter != range.second) {
                    std::copy(defIter, tempIter + 1,
                        std::back_inserter(concurrent));
                    defIter = tempIter + 1;
                } else {
                    std::copy(defIter, range.second,
                        std::back_inserter(concurrent));
                    defIter = tempIter;
                }
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
                concurrent.clear();
            }
            iter1 = range.second;
        }
        channelPriorityInfo[iter->getChannel()] = priorityTreeRoot;
        std::cout << *priorityTreeRoot << std::endl;
        iter = chRange.second;
    }
}
