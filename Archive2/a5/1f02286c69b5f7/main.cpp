#include <iostream>
#include <stdint.h>
using namespace std;

int main()
{
    uint64_t blinkRx, initTx,initTxTheoric, antDelay, fixedDelay;
    
    fixedDelay = 9584640000;
    
    antDelay = 16415;
    blinkRx = 15042422316;
    initTx = 24627078687;
    
    initTxTheoric = (blinkRx + fixedDelay)&(0x00FFFFFFFE00);
    
    cout <<(uint64_t) (initTx - initTxTheoric - antDelay)<< endl;


}
