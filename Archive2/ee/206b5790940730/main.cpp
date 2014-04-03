#include <iostream>
#include <cstdlib>
#include <cassert>


class IO
{
public:
    enum
    {    PDM3D = 0,PAW,PATCH,MPATCH,CLM,FDET,FCHECK,MFCHECK,TRACKER,TPS,
         AAM_POIC,PDM2D,AAM_POIC_F,SINIT,LINPATCH,CLP,CLD,TRACKER4,NONLINPATCH,
         MIXPATCH,CLM3,CLMix,PRA,ATM_PO,LBPHISTPATCH,FACEPREDICTORPRA,
         FACEPREDICTORKSMOOTH,MYFACETRACKER,MYFACETRACKERPARAMS,REGOCHECK,
         MVREGOCHECK,SHAPEPREDICTORLIST, SHAPEPREDICTOR, SHAPEEXPMAP,
         DUMMY_LAST_DONT_USE
    };
};

class IOBinary : public IO
{
public:
    enum{PDM3D= IO::DUMMY_LAST_DONT_USE+1,PAW,PATCH};
};

int main(int argc, char *argv[])
{
    int type = IOBinary::PAW;
    assert(type == IOBinary::PAW);
    std::cout << type << std::endl;
    return 0;
}