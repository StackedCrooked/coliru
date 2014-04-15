#include "cpucore.h"

using namespace Numapp;

CpuCore::CpuCore(u_int32 inCoreID) : mCoreID(inCoreID)
{
    // Nothing to do
}

CpuCore::CpuCore(const CpuCore & inCpuCore) : mCoreID(inCpuCore.mCoreID)
{
    // Nothing to do
}

CpuCore::~CpuCore()
{
    // Nothing to do
}
