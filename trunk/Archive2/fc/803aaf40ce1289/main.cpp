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
 * Represents the szPriorityLevel field in the
 * ModuleNamesTable<p>
 *
 * the szPriority Field contains a channel, priority character
 * [A-Z] (from highest priority to -lowest priority)
 * and an optional sequence number.
 */
class PriorityLevel {
public:
    /**
    *
    * @param rChannel [in] channel number
    * @param priorityChar
    *                 [in] priority character - upper case
    *                 ASCII char [A-Z] where A represents the
    *                 highest priority
    * @param rSequenceNum
    *                 [in] optional sequence number [1-N] -
    *                 which when present is used to schedule
    *                 usage with the thread pool.  If this is
    *                 present it represents a lower priority level
    *                 compared to just a channel and priority
    *                 character.
    */
    explicit PriorityLevel(
        const int32_t& rChannel = 0,
        const char priorityChar = 'Z',
        const boost::optional<int32_t>& rSequenceNum =
        boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar & ~(1 << 5))
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
     * lexicographical nature of the comparison<p>
     * Note: presence of sequence number => lower priority
     *
     * @param rhs    [in] PriorityLevel to compare against
     *
     * @return 'true' if this has lower priority than rhs
     */
    inline bool operator<(const PriorityLevel& rhs) const {
        // presence of sequence number => lower priority
        const auto seqNum = mSequenceNum ? /*mSequenceNum.get()*/0 : 1;
        const auto rhsSeqNum = rhs.mSequenceNum ? /*rhs.mSequenceNum.get()*/0 : 1;
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        // use lhs > rhs to fix priority inversion
        return std::tie(mChannel, prtyChar, seqNum) >
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
    }

    // operator>=() is opposite to operator<()
    inline bool operator>=(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
    }

    /**
     * operator>() implemented so that it now works with std::sort()
     * preserving the strict weak ordering mathematical rules<p>
     * Note: presence of sequence number => lower priority
     *
     * @param rhs    [in] PriorityLevel to compare to
     *
     * @return 'true' if this has higher priority than rhs
     */
    inline bool operator>(const PriorityLevel& rhs) const {
        // presence of sequence number => lower priority
        auto seqNum = mSequenceNum ? /*mSequenceNum.get()*/ 0 : 1;
        auto rhsSeqNum = rhs.mSequenceNum ? /*rhs.mSequenceNum.get()*/ 0 : 1;
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        // use lhs > rhs to fix priority inversion
        return std::tie(mChannel, prtyChar, seqNum) <
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
    }

    /**
     * operator<=() is opposite to operator>()
     *
     * @param rhs    [in] PriorityLevel to compare to
     *
     * @return true if this <= rhs
     */
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
     *                  [in] module name - equivalent to an IP
     *                  address from a uniqueness perspective
     * @param rModuleIPAddr
     *                  [in] module's IP address
     * @param rModuleNICAddr
     *                  [in] module's NIC IP address.  Note: the DMU
     *                  will have this field blank
     * @param mModulePartNum
     *                  [in] part number
     * @param rPriority [in] SLDB Priority object with strict weak
     *                  ordering priorities according to the
     *                  requirements
     */
    explicit SLDBConfigParams(
        const std::string& rDRFileName = std::string(),
        const std::string& rModuleName = std::string(),
        const std::string& rModuleIPAddr = std::string(),
        const std::string& rModuleNICAddr = std::string(),
        const std::string& mModulePartNum = std::string(),
        const PriorityLevel& rPriority = PriorityLevel())
        : mDRFileName(rDRFileName)
        , mModuleName(rModuleName)
        , mModuleIPAddr(rModuleIPAddr)
        , mModuleNICAddr(rModuleNICAddr)
        , mModulePartNum(mModulePartNum)
        , mPriority(rPriority)
    {}

    // copy constructor
    SLDBConfigParams(const SLDBConfigParams& rhs)
        : mDRFileName(rhs.mDRFileName)
        , mModuleName(rhs.mModuleName)
        , mModuleIPAddr(rhs.mModuleIPAddr)
        , mModuleNICAddr(rhs.mModuleNICAddr)
        , mModulePartNum(rhs.mModulePartNum)
        , mPriority(rhs.mPriority)
    {}

    // move constructor
    SLDBConfigParams(SLDBConfigParams&& rhs)
        : mDRFileName(std::move(rhs.mDRFileName))
        , mModuleName(std::move(rhs.mModuleName))
        , mModuleIPAddr(std::move(rhs.mModuleIPAddr))
        , mModuleNICAddr(std::move(rhs.mModuleNICAddr))
        , mModulePartNum(std::move(rhs.mModulePartNum))
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
        swap(mModuleIPAddr, rhs.mModuleIPAddr);
        swap(mModuleNICAddr, rhs.mModuleNICAddr);
        swap(mModulePartNum, rhs.mModulePartNum);
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
    inline std::string getDRFileName() const {
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
            //<< "], ip[" << rhs.mModuleIPAddr
            //<< "], nic[" << rhs.mModuleNICAddr
            << "], prty[" << rhs.mPriority
            //<< "], pn[" << rhs.mModulePartNum
            << "], dr/xr[" << rhs.mDRFileName
            << "]";
        return os;
    }

    // directory filename
    std::string mDRFileName;

    // module name
    std::string mModuleName;

    // module IP address pair
    std::string mModuleIPAddr;

    // module NIC address
    std::string mModuleNICAddr;

    // part number - see banner
    std::string mModulePartNum;

    // channel priority level
    PriorityLevel mPriority;
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
template <typename Param>
struct PriorityNode {
    // default explicit constructor
    explicit PriorityNode(const size_t& rDepth = 0)
        : mConcurrent()
        , mRunningPeerCount(-1)
        , mNextNode(nullptr)
        , mDepth(rDepth)
        , mDone(false)
    {}

    // copy constructor
    PriorityNode(const PriorityNode& rhs)
        : mConcurrent(rhs.mConcurrent)
        , mRunningPeerCount(rhs.mRunningPeerCount)
        , mNextNode(rhs.mNextNode)
        , mDepth(rhs.mDepth)
        , mDone(rhs.mDone)
    {}

    // move constructor
    PriorityNode(PriorityNode&& rhs)
        : mConcurrent(std::move(rhs.mConcurrent))
        , mRunningPeerCount(std::move(rhs.mRunningPeerCount))
        , mNextNode(std::move(rhs.mNextNode))
        , mDepth(std::move(rhs.mDepth))
        , mDone(std::move(rhs.mDone))
    {}

    // non-throwing copy-and-swap idiom unified assignment
    inline PriorityNode& operator=(PriorityNode rhs) {
        rhs.swap(*this);
        return *this;
    }

    // non-throwing-swap idiom
    inline void swap(PriorityNode& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // swap base members
        //Base::swap(rhs);
        // swap members here
        swap(mConcurrent, rhs.mConcurrent);
        swap(mRunningPeerCount, rhs.mRunningPeerCount);
        swap(mNextNode, rhs.mNextNode);
        swap(mDepth, rhs.mDepth);
        swap(mDone, rhs.mDone);
    }

    // destructor
    virtual ~PriorityNode() = default;

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] PriorityNode<Param> to send to the output
     *               stream.
     *
     * @return a reference to the updated stream
     */
    friend std::ostream& operator<<(
        std::ostream& os, const PriorityNode& rhs) {
        // indent 3 spaces per depth level
        std::string indent = rhs.mDepth > 0 ?
            std::string(rhs.mDepth, '-') + ">" :
            std::string();
        // print out the concurrent threads that
        // can be scheduled with the thread pool
        for (const auto& next : rhs.mConcurrent) {
            os << indent << next << std::endl;
        }
        // print the dependent priorities that can only
        // be scheduled when the concurrent ones are finished
        if (rhs.mNextNode) {
            //recursive node print - no need for std::endl at end
            os << *rhs.mNextNode;
        }
        return os;
    }

    /**
     * recursive scheduling method to schedule a parameter for the
     * thread pool.
     *
     * @param rParam
     */
    void schedule(const Param& rParam) {
        // search mConcurrent for a duplicate
        const auto& iter = std::find_if(
            mConcurrent.cbegin(), mConcurrent.cend(),
            [&rParam](const SLDBConfigParams& next) {
                return next.getModuleName() ==
                    rParam.getModuleName();
            });
        if (iter != mConcurrent.cend()) {
            std::vector<Param> concurrent = { rParam };
            if (!mNextNode) {
                mNextNode = std::make_shared <
                    PriorityNode<Param>> (mDepth + 1);
            }
            mNextNode->schedule(rParam);
        } else {
            mConcurrent.push_back(rParam);
        }
    }

    //template <>

    //void PriorityNode<SLDBConfigParams>::schedule(const SLDBConfigParams& rParam);

    // these are all equivalent thread priorities
    // that can be run simultaneously
    std::vector<Param> mConcurrent;

    // used for peer counting
    int32_t mRunningPeerCount;

    // these are concurrent threads that must be AFTER all
    // mConcurrent tasks have completed (exiting the thread pool)
    std::shared_ptr<PriorityNode<Param>> mNextNode;

    // recursion depth
    size_t mDepth;

    // flag indicating finished enqueueing all this node's mConcurrent tasks
    bool mDone;
};

//template <>

//void PriorityNode<SLDBConfigParams>::schedule(const SLDBConfigParams& rParam) {
//}

int main()
{

    // more realistic priorities - C++11 brace initialization syntax
    std::vector<SLDBConfigParams> parameterInfo = {
        // channel[1] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic2", "", "", "", PriorityLevel(1, 'A')),
        SLDBConfigParams("jeppall._dr", "nic2", "", "", "", PriorityLevel(1, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm4", "", "", "", PriorityLevel(1, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm4", "", "", "", PriorityLevel(1, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc2", "", "", "", PriorityLevel(1, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc2", "", "", "", PriorityLevel(1, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio1b", "", "", "", PriorityLevel(1, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "gio1b", "", "", "", PriorityLevel(1, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio2", "", "", "", PriorityLevel(1, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio2", "", "", "", PriorityLevel(1, 'B', 4)),

        // channel[2] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic5", "", "", "", PriorityLevel(2, 'A')),
        SLDBConfigParams("jeppall._dr", "nic5", "", "", "", PriorityLevel(2, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm2", "", "", "", PriorityLevel(2, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm2", "", "", "", PriorityLevel(2, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc5", "", "", "", PriorityLevel(2, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc5", "", "", "", PriorityLevel(2, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio5", "", "", "", PriorityLevel(2, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "gio5", "", "", "", PriorityLevel(2, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "csio3", "", "", "", PriorityLevel(2, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "csio3", "", "", "", PriorityLevel(2, 'B', 4)),

        //channel[3] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic6", "", "", "", PriorityLevel(3, 'A')),
        SLDBConfigParams("jeppall._dr", "nic6", "", "", "", PriorityLevel(3, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm1", "", "", "", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm1", "", "", "", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc6", "", "", "", PriorityLevel(2, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc6", "", "", "", PriorityLevel(3, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "egpwm1", "", "", "", PriorityLevel(3, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "egpwm1", "", "", "", PriorityLevel(3, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "cio3", "", "", "", PriorityLevel(2, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "cio3", "", "", "", PriorityLevel(3, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio6", "", "", "", PriorityLevel(3, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio6", "", "", "", PriorityLevel(3, 'B', 4)),

        // channel[4] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "rnic1", "", "", "", PriorityLevel(4, 'A')),
        SLDBConfigParams("jeppall._dr", "rnic1", "", "", "", PriorityLevel(4, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "rproc1", "", "", "", PriorityLevel(4, 'B')),
        SLDBConfigParams("jeppall._dr", "rproc1", "", "", "", PriorityLevel(4, 'B')),

        // channel[5] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "rnic2", "", "", "", PriorityLevel(5, 'A')),
        SLDBConfigParams("jeppall._dr", "rnic2", "", "", "", PriorityLevel(5, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "rproc2", "", "", "", PriorityLevel(5, 'B')),
        SLDBConfigParams("jeppall._dr", "rproc2", "", "", "", PriorityLevel(5, 'B')),

        // channel 6
        SLDBConfigParams("envmoddir._dr", "nic1", "192.168.1.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic1", "192.168.1.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'A')),
        SLDBConfigParams("jeppall._dr", "nic1", "192.168.1.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'A')),
        SLDBConfigParams("tfsdir._dr", "nic1", "192.168.1.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'A')),
        SLDBConfigParams("threatdir._dr", "nic1", "192.168.1.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'A')),

        SLDBConfigParams("envmoddir._dr", "aiopa1", "192.168.1.18", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "aiopa1", "192.168.1.18", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "aiopa1", "192.168.1.18", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("tfsdir._dr", "aiopa1", "192.168.1.18", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 2)),
        SLDBConfigParams("threatdir._dr", "aiopa1", "192.168.1.18", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 2)),

        SLDBConfigParams("envmoddir._dr", "proc1", "192.168.193.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc1", "192.168.193.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "proc1", "192.168.193.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("tfsdir._dr", "proc1", "192.168.193.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("threatdir._dr", "proc1", "192.168.193.1", "192.168.1.1", "7038231-1902", PriorityLevel(6, 'B', 1)),

        SLDBConfigParams("envmoddir._dr", "agm1", "192.168.13.1", "192.168.1.1", "7038231-1902", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm1", "192.168.13.1", "192.168.1.1", "7038231-1902", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm1", "192.168.13.1", "192.168.1.1", "7038231-1902", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("tfsdir._dr", "agm1", "192.168.13.1", "192.168.1.1", "7038231-1902", PriorityLevel(3, 'B', 1)),
        SLDBConfigParams("threatdir._dr", "agm1", "192.168.13.1", "192.168.1.1", "7038231-1902", PriorityLevel(3, 'B', 1)),


        // channel[7] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic1", "", "", "", PriorityLevel(7, 'A')),
        SLDBConfigParams("jeppall._dr", "nic1", "", "", "", PriorityLevel(7, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc1", "", "", "", PriorityLevel(6, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "proc1", "", "", "", PriorityLevel(7, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "aiopa1", "", "", "", PriorityLevel(7, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "aiopa1", "", "", "", PriorityLevel(7, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "aiopb1", "", "", "", PriorityLevel(6, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "aiopb1", "", "", "", PriorityLevel(7, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "cio1", "", "", "", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "cio1", "", "", "", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio1a", "", "", "", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio1a", "", "", "", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "csio1", "", "", "", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "csio1", "", "", "", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio1", "", "", "", PriorityLevel(6, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio1", "", "", "", PriorityLevel(7, 'B', 4)),

        // channel[8] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic3", "", "", "", PriorityLevel(8, 'A')),
        SLDBConfigParams("jeppall._dr", "nic3", "", "", "", PriorityLevel(8, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm3", "", "", "", PriorityLevel(7, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm3", "", "", "", PriorityLevel(8, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc3", "", "", "", PriorityLevel(7, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc3", "", "", "", PriorityLevel(8, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "egpwm2", "", "", "", PriorityLevel(7, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "egpwm2", "", "", "", PriorityLevel(8, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio2a", "", "", "", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio2a", "", "", "", PriorityLevel(8, 'B', 4)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio3", "", "", "", PriorityLevel(7, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "gio3", "", "", "", PriorityLevel(8, 'B', 4)),

        // channel[9] task tree
        SLDBConfigParams("INAVDATAHI_16M._xr", "nic5", "", "", "", PriorityLevel(9, 'A')),
        SLDBConfigParams("jeppall._dr", "nic6", "", "", "", PriorityLevel(9, 'A')),
        SLDBConfigParams("INAVDATAHI_16M._xr", "agm2", "", "", "", PriorityLevel(9, 'B', 1)),
        SLDBConfigParams("jeppall._dr", "agm3", "", "", "", PriorityLevel(9, 'B', 1)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "proc5", "", "", "", PriorityLevel(9, 'B', 2)),
        SLDBConfigParams("jeppall._dr", "proc6", "", "", "", PriorityLevel(9, 'B', 2)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "gio5", "", "", "", PriorityLevel(9, 'B', 3)),
        SLDBConfigParams("jeppall._dr", "gio6", "", "", "", PriorityLevel(9, 'B', 3)),
        SLDBConfigParams("INAVDATAHI_16M._xr", "csio3", "", "", "", PriorityLevel(9, 'B', 4)),
        SLDBConfigParams("jeppall._dr", "csio4", "", "", "", PriorityLevel(9, 'B', 4)),

        // channel[10] task tree
        SLDBConfigParams("jeppall._dr", "cmc", "", "", "", PriorityLevel(10, 'Z'))
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

    // split the task priorities into 2 types:
    // channel + Z level priority & channel + Level (<Z) &
    // Optional sequence priorities - preserving order
    auto lowPriorityIter = std::stable_partition(
        parameterInfo.begin(), parameterInfo.end(),
        [](const SLDBConfigParams& params) {
        return params.mPriority.mPriorityChar != 'Z';
    });

    std::vector<std::pair<std::vector<SLDBConfigParams>::const_iterator,
        std::vector<SLDBConfigParams>::const_iterator >> ranges;

    ranges.emplace_back(make_pair(parameterInfo.cbegin(), lowPriorityIter));

    if (lowPriorityIter != parameterInfo.cend()) {
        ranges.emplace_back(make_pair(lowPriorityIter, parameterInfo.cend()));
    }

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
        // priority inversion fix
        return lhs.getPriorityLevel() <
            rhs.getPriorityLevel();
    };

    // convert the MLF/_DR files into a sort of priority tree organized by channel
    std::map<int32_t, std::shared_ptr<PriorityNode<SLDBConfigParams>>> priorityInfo;

    // iterate over each of the channel ranges leaving the Z level priorities
    // as the last range - optional if present
    for (const auto& taskRange : ranges) {
        // iterate over each of the channel ranges
        for (auto iter = taskRange.first; iter != taskRange.second;){
            // get the next group of channel parameters
            auto chRange = std::equal_range(iter, taskRange.second, *iter, gChannelPred);
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
            auto rootNode = std::make_shared <
                PriorityNode<SLDBConfigParams>>();
            auto node = rootNode;
            for (auto iter1 = chParams.begin(); iter1 != chParams.end();) {
                // matching priories using gPriorityPred to find matches
                // the orderedParams must also be ordered using this predicate
                const auto& range = std::equal_range(iter1,
                    chParams.end(), *iter1, gPriorityLevelPred);
#if 0
                std::cout << "channel [" << iter->getChannel()
                    << "] next priority band" << std::endl;
                std::cout << "==============================" << std::endl;
                std::copy(range.first, range.second,
                    std::ostream_iterator<SLDBConfigParams>(std::cout, "\n"));
                std::cout << std::endl;
#endif
                // recursive scheduler
                std::for_each(range.first, range.second,
                    [&](const SLDBConfigParams& next) {
                    node->schedule(next);
                });
#if 0
                std::cout << "temp [" << iter->getChannel() << "] task tree" << std::endl;
                std::cout << *rootNode << std::endl;
#endif
                while (node->mNextNode) {
                    node = node->mNextNode;
                }
                node->mNextNode = std::make_shared <
                    PriorityNode<SLDBConfigParams>>(
                        node->mDepth + 1);
                node = node->mNextNode;
                iter1 = range.second;
            }
            priorityInfo[iter->getChannel()] = node;
            std::cout << "channel [" << iter->getChannel() << "] task tree" << std::endl;
            std::cout << *rootNode << std::endl;
            iter = chRange.second;
        }
    }
}
