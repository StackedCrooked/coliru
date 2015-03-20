#include <iostream>
#include <cxxabi.h>
#include <string>

#include <vector>

enum MigrationPhase_t {
    kForwardToTPF,
    kTPFMaster,
    kOBEMaster,
    kFullObe,
    kDefaultMigtrationPhase
};

template<MigrationPhase_t mig>
class Stringify
{
    public:
    static const std::string& getName();
};


const std::string& Stringify<MigrationPhase_t mig>::getName()
{
    #define MIGRATION_STR(enum_value) \
      #enum_value

    static std::string a( MIGRATION_STR(mig) );
    return a;
    
    #undef MIGRATION_STR
}

class Stringify<kForwardToTPF>;
class Stringify<kTPFMaster>;
class Stringify<kOBEMaster>;
class Stringify<kFullObe>;
class Stringify<kDefaultMigtrationPhase>;


int main()
{
    const MigrationPhase_t aMigP = kTPFMaster;
    std::cout << Stringify<kTPFMaster>::getName() << std::endl;
}
