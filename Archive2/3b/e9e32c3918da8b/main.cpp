#include <string>
#include <array>
#include <iostream>

class Element{
    public:
       enum class groupNames {  HYDROGEN, ALKALI, ALKALINE, GROUP_THREE, GROUP_FOUR, GROUP_FIVE,
                                GROUP_SIX, GROUP_SEVEN, GROUP_EIGHT, GROUP_NINE, GROUP_TEN,
                                GROUP_ELEVEN,GROUP_TWELVE, GROUP_THIRTEEN, GROUP_FOURTEEN,
                                GROUP_FIFTEEN, CHALCOGEN, HALOGEN, NOBLE_GAS
                                };
        enum class orbitals {ORBITAL_NOTSET, S_ORBITAL, P_ORBITAL, D_ORBITAL, F_ORBITAL};
        enum class metal_status {METAL = 0, METALLOID, NONMETAL};
        Element() = default ;
        Element( int aNumber, int pNumber, groupNames groupnames, metal_status MetalStatus, orbitals Orbital,
                 std::string eName, std::string eSybol) ;
        void displayProperties();

    private:
        groupNames groupNumber = groupNames::HYDROGEN ;
        orbitals orbital = orbitals::ORBITAL_NOTSET ;
        metal_status metalStatus = metal_status::METAL ;
        std::string elementSymbol; 
        std::string elementName;
        int atomicNumber = 0 ;
        int periodNumber = 0 ;
};

Element::Element( int aNumber, int pNumber, groupNames groupnames, metal_status MetalStatus, orbitals Orbital, 
                  std::string eName, std::string eSymbol ) : elementSymbol(eSymbol), elementName(eName)
{
    groupNumber = groupnames;
    metalStatus = MetalStatus;
    orbital = Orbital;
    atomicNumber = aNumber;
    periodNumber = pNumber;
    // elementName = eName;
    // elementSymbol = eSymbol;
}

// ...

std::array< Element, 115 > Elements
{
    {
        {},
        { 1,1, Element::groupNames::HYDROGEN, Element::metal_status::NONMETAL, Element::orbitals::S_ORBITAL, "Hydrogen", "H" },
        // { .... },
        // ...
    }
};

int main()
{
}