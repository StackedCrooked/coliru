#include <stdint.h>
#include <iostream>

int64_t GetOldDustThreshold(size_t nSize, int64_t nRelayTxFee = 1000)
{
    // Based on Bitcoin Core 0.9
    return 1 + (((nSize * nRelayTxFee * 3) - 1) / 1000);
}

int64_t GetNewDustThreshold(size_t nSize, int64_t nRelayTxFee = 1000)
{
    // Based on Bitcoin Core 0.10
    return (nRelayTxFee * nSize / 1000) * 3;
}

bool isEqual(size_t nSize, int64_t nRelayTxFee = 1000)
{
    int64_t nDustLimitOld = GetOldDustThreshold(nSize, nRelayTxFee);
    int64_t nDustLimitNew = GetNewDustThreshold(nSize, nRelayTxFee);

    return nDustLimitOld == nDustLimitNew;
}

int main() 
{
    int64_t nRelayTxFee = 1000;
    
    for (size_t nSize = 1; nSize < 10000; ++nSize)
    {
        if (!isEqual(nSize, nRelayTxFee))
        {
            std::cout << "Error for nSize: " << nSize << std::endl;
            std::cout << "Old threshold: " << GetOldDustThreshold(nSize, nRelayTxFee) << std::endl;
            std::cout << "New threshold: " << GetNewDustThreshold(nSize, nRelayTxFee) << std::endl;

            return 1;
        }
    }
    
    std::cout << "Success! The calculations have a similar outcome." << std::endl;

    return 0;
}