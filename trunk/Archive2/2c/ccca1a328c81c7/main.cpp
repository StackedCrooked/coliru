#include <map>

typedef std::map <uint16_t, int> mapType;

typedef std::pair <uint16_t, int> mapPair;

struct className{
    className ();
    mapType m_mapName; 
};

className::className () 
:m_mapName{ 
    {0, 0}, 
    {1, 0}, 
    {2, 0}}
{}

int main() {
    className a;
}