#include "snapshot.h"
#include <algorithm>


Snapshot::Snapshot() :
    mPackets(0),
    mBytes(0),
    mMinSize(0),
    mMaxSize(0),
    mTimeFirst(0),
    mTimeLast(0)
{
}

#ifdef REF
void Snapshot::update(const Counter& repeats, const Size& size, const Time& time)
#else // by value
void Snapshot::update(Counter repeats, Size size, Time time)
#endif
{
    for (auto i = 0 * repeats; i != repeats; ++i)
    {
        mPackets++;
        mBytes += size;
        mTimeLast = time;

        mMinSize = std::min(mMinSize, size);
        mMaxSize = std::max(mMaxSize, size);
    }
}
