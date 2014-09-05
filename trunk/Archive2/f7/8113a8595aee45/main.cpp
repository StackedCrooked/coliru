#include <iostream>
#include <string>
#include <vector>
#include <queue>
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

struct PriorityElem {
    PriorityElem (const int& rChannel, const char priority, const boost::optional<int>& rSequenceNum = boost::optional<int>()) 
        : mChannel(rChannel)
        , mPriority(priority)
        , mSequenceNum(rSequenceNum)
    {}
    
    // comparator that orders the elements in the priority_queue<PriorityElem>
    inline bool operator<(const PriorityElem& rhs) const {
        // compare tuples in left to right order using < operator
        return std::tie(mChannel, mPriority, mSequenceNum) <
            std::tie(rhs.mChannel, rhs.mPriority, rhs.mSequenceNum);
    }

    // friendly for streaming
    inline friend std::ostream& operator << (std::ostream& os, const PriorityElem& val) {
        os << "channel[" << val.mChannel << "], priority[" << val.mPriority << "]";
        if (val.mSequenceNum) {
            os << " sequenceNum[" << val.mSequenceNum << "]";
        }
        return os;
    }    
    int mChannel;
    char mPriority;
    boost::optional<int> mSequenceNum;
};

int main()
{    
    auto comparator = []( const PriorityElem& lhs, const PriorityElem& rhs ) { 
        return lhs < rhs; 
    };
    
    std::vector<PriorityElem> testVec = {
        PriorityElem(1, 'A', 2),
        PriorityElem(1, 'B', 3)
    };
    
    for (const auto& next : testVec) {
       // std::cout << next << std::endl;
    }
    std::cout << testVec << std::endl;
    
    //std::priority_queue<PriorityElem, std::vector<PriorityElem>, decltype(comparator)> myPriorityQueue(comparator);
}
