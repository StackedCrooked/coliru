#ifndef CPUCORE_H
#define CPUCORE_H

#include "coretypes.h"

namespace Numapp {

/**
 *
 **/
class CpuCore
{
public:
    /**
     * Constructor
     **/
    CpuCore(uint32 inCoreID);

    /**
     * Copy-constructor
     **/
    CpuCore(const CpuCore & inCpuCore);

    /**
     * Destructor
     **/
    ~CpuCore();

    /**
     *
     **/
    inline uint32 getCoreID() {
        return this->mCoreID;
    }

private:
    uint32 mCoreID;
};

}
#endif // CPUCORE_H
