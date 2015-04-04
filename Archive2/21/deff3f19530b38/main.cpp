#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <cstdint>

using Counter = int32_t;
using Size = int16_t;
using Time = int64_t;

struct Snapshot
{
    Snapshot();

    #ifdef REF
    void update(const Counter& repeats, const Size&, const Time&);
    #else // by value
    void update(Counter repeats, Size, Time);
    #endif

    Counter mPackets;
    Counter mBytes;
    Size mMinSize;
    Size mMaxSize;
    Time mTimeFirst;
    Time mTimeLast;
};

#endif // SNAPSHOT_H
