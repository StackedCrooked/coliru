#include <iostream>
#include <sstream>
#include <iostream>
#include <iterator>
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
 *  represents the szPriorityLevel in the MLF ModuleNamesTable<p>
 *
 * the szPriority Field contains a channel, priority character
 * [A-Z] (from highest priority to -lowest priority)
 * and an optional sequence number.
 */
class PriorityLevel {
public:
    // default constructor
    explicit PriorityLevel(
        const int32_t& rChannel = -1,
        const char priorityChar = 'Z',
        const std::string& rDRFileName = std::string(),
        const boost::optional<int32_t>& rSequenceNum =
            boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar)
        , mDRFileName(rDRFileName)
        , mSequenceNum(rSequenceNum)
    {}

    // copy constructor
    PriorityLevel(const PriorityLevel& rhs)
        : mChannel(rhs.mChannel)
        , mPriorityChar(rhs.mPriorityChar)
        , mDRFileName(rhs.mDRFileName)
        , mSequenceNum(rhs.mSequenceNum)
    {}

    // move constructor
    PriorityLevel(PriorityLevel&& rhs)
        : mChannel(std::move(rhs.mChannel))
        , mPriorityChar(std::move(rhs.mPriorityChar))
        , mDRFileName(std::move(rhs.mDRFileName))
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
        swap(mDRFileName, rhs.mDRFileName);
        swap(mSequenceNum, rhs.mSequenceNum);
    }

    // non-throwing copy-and-swap idiom unified assignment
    PriorityLevel& operator=(PriorityLevel rhs) {
        rhs.swap(*this);
        return *this;
    }

    // equality operator
    inline bool operator==(const PriorityLevel& rhs) const {
        return std::tie(mChannel, mPriorityChar, mDRFileName, mSequenceNum) ==
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mDRFileName, rhs.mSequenceNum);
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
        return std::tie(mChannel, mPriorityChar, mDRFileName, seqNum) >
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mDRFileName, rhsSeqNum);
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
        return std::tie(mChannel, mPriorityChar, mDRFileName, seqNum) <
            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mDRFileName, rhsSeqNum);
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

//private:
    // string representation of the priority string
    inline std::string getPriorityStr() const {
        std::stringstream ss;
        ss << mChannel << mPriorityChar << mDRFileName;
        if (mSequenceNum) {
            ss << mSequenceNum.get();
        }
        return ss.str();
    }

    // channel number - top level order field
    int32_t mChannel;
    // single upper case character A=>'highest priority'
    char mPriorityChar;
    // name of the module/nic associated with this priority
    std::string mDRFileName;
    // optional field - when present indicates start order
    boost::optional<int32_t> mSequenceNum;
};


int main()
{    
    // more realistic priorities from 'Dassault' MLF
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
        PriorityLevel(2, 'A', "[foo._dr]"),
        PriorityLevel(2, 'B', "[foo._dr]", 1),
        PriorityLevel(2, 'B', "[foo._dr]", 2),
        PriorityLevel(2, 'B', "[foo._dr]", 3),
        PriorityLevel(2, 'B', "[foo._dr]", 2)
    };

    // order the priorities in ascending order
    std::sort(gPriorities.begin(), gPriorities.end(),
        std::greater<PriorityLevel>());
    std::copy(gPriorities.begin(), gPriorities.end(),
        std::ostream_iterator<PriorityLevel>(std::cout, "\n"));
    std::cout << std::endl;
    
    const auto channelComp = [](const PriorityLevel& a, const PriorityLevel& b) {
        return a.mChannel < b.mChannel;
    };    

    // please help, I do not know how to apply equal range or some
    // other algorithm to find the [range.first, range.second) with 
    // elements that match just the channel character
    auto range = std::equal_range(gPriorities.begin(), gPriorities.end(), 1, channelComp);
    auto rangeLength = std::distance(range.first, range.second);
    // print all common channel entries
    std::copy(range.first, range.second,
        std::ostream_iterator<PriorityLevel>(std::cout, "\n"));
    std::cout << std::endl;    
}