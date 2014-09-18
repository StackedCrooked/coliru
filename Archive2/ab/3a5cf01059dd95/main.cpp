#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <boost/optional.hpp>

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
        return this->getPriorityStr() == rhs.getPriorityStr();
        
    }

    // inequality operator
    inline bool operator!=(const PriorityLevel& rhs) const {
        return !(operator==(rhs));
    }

    inline bool operator<(const PriorityLevel& rhs) const {
        std::cout << getPriorityStr() << " vs. " << rhs.getPriorityStr() << std::endl;
        return getPriorityStr() < rhs.getPriorityStr();
    }

    inline bool operator>(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
    }

    inline friend std::ostream& operator << (
        std::ostream& os, const PriorityLevel& rhs) {
        os << rhs.getPriorityStr();
        return os;
    }

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

static std::vector<PriorityLevel> gPriorities = {
    PriorityLevel(1, 'A', 3),
    PriorityLevel(2, 'A'),
    PriorityLevel(2, 'A'),      // duplicates cause visual studio std::greater<PriorityLevel> to crash comment out and vs works!!!
    PriorityLevel(3, 'A', 1)
};

int main()
{
    // order the priorities in ascending order - suitable for a priority queue
    std::sort(gPriorities.begin(), gPriorities.end(), std::less<PriorityLevel>());
    std::copy(gPriorities.begin(), gPriorities.end(), 
        std::ostream_iterator<PriorityLevel>(std::cout, "\n"));
    std::cout << std::endl;
    // order the priorities in descending order - breaks on 
    // Visual Studio when duplicate entries in gPriorities
    std::sort(gPriorities.begin(), gPriorities.end(), std::less<PriorityLevel>());
    std::copy(gPriorities.begin(), gPriorities.end(), 
        std::ostream_iterator<PriorityLevel>(std::cout, "\n"));
            
}
