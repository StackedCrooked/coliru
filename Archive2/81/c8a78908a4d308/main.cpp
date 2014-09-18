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
    {}

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
//        return std::tie(mChannel, mPriorityChar, mSequenceNum) ==
//            std::tie(rhs.mChannel, rhs.mPriorityChar, rhs.mSequenceNum);
        return getPriorityStr() == rhs.getPriorityStr();

    }

    // inequality operator
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
//        auto len = getPriorityStr().length();
//        auto rhsLen = rhs.getPriorityStr().length();
//        auto seqNum = mSequenceNum ? mSequenceNum.get() : 0;
//        auto rhsSeqNum = rhs.mSequenceNum ? rhs.mSequenceNum.get() : 0;
//        return std::tie(len, mPriorityChar, mChannel, seqNum) >
//            std::tie(rhsLen, rhs.mPriorityChar, rhs.mChannel, rhsSeqNum);
        return getPriorityStr() < rhs.getPriorityStr();
    }

    // comparator used to maintain elements in priority order
    inline bool operator>(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
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
        ss << mChannel << mPriorityChar;
        if (mSequenceNum) {
            ss << mSequenceNum.get();
        }
        return ss.str();
    }

    // channel number
    int32_t mChannel;
    // single upper case character A=>'highest priority'
    char mPriorityChar;
    // optional field - when present indicates start order
    boost::optional<int32_t> mSequenceNum;
};

int main()
{    
    std::vector<PriorityLevel>  gPriorities = {
        PriorityLevel(2, 'A', 1),
        PriorityLevel(2, 'A'),
        PriorityLevel(2, 'A'), //  DUPLICATE ENTRY HERE CAUSES std::sort to throw assertion error when using std::greater<T>
    };
    // order the priorities in highest to lowest order - suitable for a priority queue
    std::sort(gPriorities.begin(), gPriorities.end(), std::greater<PriorityLevel>());
    std::copy(gPriorities.begin(), gPriorities.end(), 
        std::ostream_iterator<PriorityLevel>(std::cout, "\n"));
    std::cout << std::endl;
    
    //this will break if there are duplicate entries in Visual Studio - not in gcc
    std::sort(gPriorities.begin(), gPriorities.end(), std::greater<PriorityLevel>());
    std::copy(gPriorities.begin(), gPriorities.end(), 
        std::ostream_iterator<PriorityLevel>(std::cout, "\n"));
    std::cout << std::endl;

}