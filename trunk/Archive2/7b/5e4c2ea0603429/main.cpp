#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::set<std::pair<int,int> > SetOfPair;

struct pair_equal : std::unary_function< std::pair<int,int>, bool>
{
    pair_equal(const int &idx) : idx_(idx) {}
    bool operator()(const std::pair<int,int> &arg) const { return ( arg.first == idx_) || ( arg.second == idx_); }
    const int &idx_;
};

std::set<int> connected_component( SetOfPair& sp) {
    std::vector<int> componentIndices;
    componentIndices.push_back( (*(sp.begin())).first);
    componentIndices.push_back( (*(sp.begin())).second);
    int indexCount = 2;
    int currIdx = 0;
    
    SetOfPair::const_iterator it;
    while ( currIdx < indexCount) {
        while ( ( it = std::find_if( sp.begin(), sp.end(), pair_equal( componentIndices[ currIdx]))) != sp.end()) {
            /* new reachable index connected to this component found */
            int newIdx = ( componentIndices[ currIdx] == (*it).first? (*it).second : (*it).first);
            /* insert if not present already */
            if ( std::find( componentIndices.begin(), componentIndices.end(), newIdx) == componentIndices.end()) {
                componentIndices.push_back( newIdx);
                ++indexCount;
            }
            sp.erase( it);
        }
        ++currIdx;
    }
    return std::set<int>( componentIndices.begin(), componentIndices.end());
}

int make_connected_components( SetOfPair sp, std::vector<std::set<int> >& result) {
    int componentCount = 0;
    while( !sp.empty()) {
        std::set<int> component = connected_component( sp);
        result.push_back( component);
        ++componentCount;
    }
    return componentCount;
}
/*
 * 
 */
int main(int argc, char** argv) {

    SetOfPair sp;
    sp.insert( std::make_pair<int, int>( 1, 1));
    sp.insert( std::make_pair<int, int>( 3, 2));
    sp.insert( std::make_pair<int, int>( 5, 5));
    sp.insert( std::make_pair<int, int>( 5, 4));
    sp.insert( std::make_pair<int, int>( 4, 2));
    sp.insert( std::make_pair<int, int>( 1, 8));
    sp.insert( std::make_pair<int, int>( 9, 9));
    
    std::vector<std::set<int> > components;
    int numberOfComponents = make_connected_components( sp, components);
        
    /* results */
    std::cout << "numberOfComponents:" << numberOfComponents << std::endl;
    std::vector<std::set<int> >::iterator it = components.begin();
    while ( it != components.end()) {
        std::copy( (*it).begin(), (*it).end(), std::ostream_iterator<int>( std::cout, ":"));
        std::cout << std::endl;
        ++it;
    }
    return 0;
}