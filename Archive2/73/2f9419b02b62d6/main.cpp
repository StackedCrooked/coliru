#include <iostream>
#include <vector>

#include <boost/random.hpp>

typedef boost::mt19937 RNGType;
RNGType rng;
int nParticles = 3;

std::vector<int> filter(std::vector<double> const& weights)
{
  std::vector<int> indices(nParticles);
  boost::random::discrete_distribution<int,double> weightdist(weights);
  boost::variate_generator< RNGType&, 
      boost::random::discrete_distribution<int,double> >
      weightsampler(rng, weightdist);
  for (int i=0; i<nParticles ; ++i)
  {
    indices[i] = weightsampler();
  }
  return indices;
}

int main()
{      
  std::vector<int> indices(nParticles);
  int nIterations(5);
  for (int i=0; i<nIterations; ++i)
  {
    // Pseudo code. In the final version the weights will change on each loop
    std::vector<double> weights = { 0.1, 0.4, 0.3 }; // Vector length 10
    indices = filter(weights);
    
    for(auto const& idx : indices) {
        std::cout << idx << ", ";
    }
    std::cout << '\n';
  }
}
