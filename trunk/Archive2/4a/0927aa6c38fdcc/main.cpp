using namespace std;

#include <string>
#include <algorithm>


typedef std::pair<int, std::string> Pair;

struct Cmp 
{
    bool operator()(Pair const& a, Pair const& b) const { return a.first < b.first; };
    bool operator()(Pair const& a, int & b) const { return a.first < b; };
    bool operator()(int & a, Pair const& b) const { return a < b.first; };
};

struct SectorSignalPairEquals : public std::binary_function<Pair, int, bool> {
   bool operator()(Pair const& a, int b) const
   {
      return (a.first == b);
   };
};

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cout << "Executing... \n";
    
    
    std::vector<Pair> sectorSignals = { 
        { 1, "105" }, 
        { 2, "110" }, 
        { 3, "115" },
        { 42, "120" }, 
    };
    
    std::vector<int> sCells = { 5, 43 };
    std::vector< int > sCellsInNBest(sCells.size());
    Cmp cmp;
    std::sort(sectorSignals.begin(), sectorSignals.end(), cmp);
    std::sort(sCells.begin(), sCells.end());

    std::vector<int>::iterator resIt = std::set_intersection (sCells.begin(), sCells.end(), sectorSignals.begin(), sectorSignals.end(), sCellsInNBest.begin(), cmp);
    //auto range = std::equal_range(vec.begin(), vec.end(), std::string("zus"), cmp);
    sCellsInNBest.resize(resIt-sCellsInNBest.begin());    
    if (sCellsInNBest.size() == 0)
    {
        std::cout << "There is no Secondary Cells in NBest Server";
    }
    else
    {
        std::cout << "Secondary Cells: ";
    }
    
    std::vector< int >::iterator It = sCellsInNBest.begin();
    for(; It!= sCellsInNBest.end(); ++It)
    {
       std::cout << *It << ", ";
    }
    std::cout << endl;
    SectorSignalPairEquals equals;
    std::vector<Pair>::iterator nBestIt;
    for(size_t i=0; i<sCellsInNBest.size(); ++i)
    {
       nBestIt = std::find_if(sectorSignals.begin(), sectorSignals.end(), std::bind2nd(equals, sCellsInNBest[i]));
       std::cout << "nBest.first: " << (*nBestIt).first << endl;
       std::cout << "nBest.second: " << (*nBestIt).second << endl;
    }
}

