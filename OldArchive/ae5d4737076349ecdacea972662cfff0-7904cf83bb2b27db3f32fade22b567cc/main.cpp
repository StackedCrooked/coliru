#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

//single construction of the mt random generator
boost::random::mt19937 mtRndGen;

// simple function to take a seed, a side that will determine the size of the field
// and return a vector of uniformly distributed within field size random integers
std::vector<int> genRndField(const unsigned int seed, const unsigned int side){
    mtRndGen.seed(seed); // seed the generator
    unsigned int gridsize = std::pow(static_cast<float>(side), 2.0); //size of field
    
    std::vector<int> rndField(gridsize); //create and presize vector of ints
    
    // uniform int distribution of the mt generator results over the grid's size.
    // fed to be 0 indexing friendly
    boost::random::uniform_int_distribution<> fieldDistributor(0, gridsize -1);
    
    // there's no need to re-initialize anything, the distributor/generator
    // provide state awareness and will produce consistently different results
    // within the loop at all times,
    // and consistently different result between grids for different seeds
    for( unsigned int i = 0; i < gridsize; i++){
        rndField[i] = fieldDistributor(mtRndGen);
    }
    return rndField;
}

// simple grid like pretty print of the vector
void printVect(const std::vector<int>& vect2Print, const unsigned int prettyWidth){
    for(unsigned int i= 0; i < vect2Print.size(); i++){
        std::cout << vect2Print[i];
        if((i+1)%prettyWidth == 0 && i > 0) std::cout << "\n";
        else std::cout << ", ";
    }
}

int main(){
    const unsigned int gridSide = 12;
    const unsigned int seed = 151;
    std::vector<int> rndField = genRndField(seed, gridSide);
    printVect(rndField, gridSide);
}
