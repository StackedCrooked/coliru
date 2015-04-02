#include <vector>
#include <cmath>
#include <iostream>
#include <numeric>
#include <algorithm>
 
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj) {
  os << "[";
  for(uint i = 0; i < obj.size(); ++i){
      os << obj.at(i);
      if(i+1 < obj.size()){
          os << ", ";
      }
  }
  os << "]";
  return os;
}

template<typename Ta, typename Tb>
std::vector<Ta> sort_with(const std::vector<Ta>& first, const std::vector<Tb>& second){
    std::vector<std::pair<Ta, Tb>> zip;
    for(uint i = 0; i < first.size() && i < second.size(); ++i){
        zip.emplace_back(first[i], second[i]);
    }
    
    struct {
        bool operator()(std::pair<Ta, Tb> a, std::pair<Ta, Tb> b)
        {   
            return a.second < b.second;
        }   
    } compare_second;
    
    std::sort(zip.begin(), zip.end(), compare_second);
    
    std::vector<Ta> r;
    for(auto pair : zip){
        r.push_back(pair.first);
    }
    return r;
} 
 
struct simplex_noise{
    simplex_noise(int init_seed, int dimensions): seed(hash(init_seed)), d(dimensions){
        // Compute skew constant. This is questionably correct
        f = (std::pow(d + 1, 0.5) - 1) / d;
 
        // This is the proper relation between f and g in terms of d
        // that makes sure skewing and unskewing reverse eachother
        g = f / (1 + d * f);
 
        // simplex edge length
        float sideLength = std::pow(d, 0.5) / (d * f + 1);
        float a = std::pow(std::pow(sideLength, 2) - std::pow(sideLength / 2, 2), 0.5);
 
        // distace from corner to center of most distant face
        // this is the max influance distance for a vertex
        float cornerToFace;
        if (d == 2) {
            cornerToFace = a;
        } else if (d == 1){
            cornerToFace = sideLength;
        } else{
            cornerToFace = std::pow((std::pow(a, 2) + std::pow((a/2), 2)), 0.5);
        }
        cornerToFaceSquared = std::pow(cornerToFace, 2);
 
        // Precompute gradient vectors.
        // Make all possible vectors consisting of:
        // +1 and -1 components with a single 0 component:
        // Vecs from center to midddle of edges of hyper-cube
        
        // Little helper generator function for making gradient vecs
        // Makes vecs of all -1 or 1, of d dimensions 
        auto vf = [](int dimensions){
            std::vector<std::vector<float>> vectors;
            for(int i = 0; i < std::pow(2, dimensions); ++i){
                std::vector<float> vector;
                for(int n = 0; n < dimensions; ++n){
                    vector.push_back((i >> n) % 2 * 2 -1);
                }
                vectors.push_back(vector);
            }
            return vectors;
        };
 
        if (d > 1) {
            // inject 0s into vecs from vf to make needed vecs
            for(int z = 0; z < 3; ++z) {
                auto vecs_for_d = vf(d-1);
                for(auto vector : vecs_for_d){
                    vector.insert(vector.begin() += z, 0);
                    vecs.push_back(vector);
                }
            }
            
            // All 1 or -1 version (hypercube corners)
            // Makes number of vecs higher, and a power of 2.
            //self.vecs=[v for z in xrange(d) for v in vf(d)]
            
            // Compensate for gradient vector lengths
            valueScaler = std::pow(d-1, -0.5);
            // use d instead of d-1 if using corners instead of edges
            
            // Rough estimated/expirmentally determined function
            // for scaling output to be -1 to 1
            valueScaler *= std::pow(d - 1,-3.5) *100 + 13;
        } else {
            f = 0;
            vecs.emplace_back(1.0f);
            vecs.emplace_back(-1.0f);
            valueScaler = 1.0;
            cornerToFaceSquared = 1.0;
            g = 1.0;
        }
    }
 
 
    float noise(std::vector<float> coord, bool getDerivative){
        //""" loc is a list of coordinates for the sample position """
        // Perform the skew operation on input space will convert the

        std::cout << "coord " << coord << "\n";
        
        std::vector<int> d_range(d);
        std::iota(d_range.begin(), d_range.end(), 0);

        // regular simplexs to right simplexes making up huper-cubes
        auto s = std::accumulate(coord.begin(), coord.end(), 0);
        // Skew and round loc to get origin of containing hypercube in skewed space
        std::vector<int> skewed_coord;
        for(auto v : coord){
            skewed_coord.push_back((int) std::floor(v + s));
        }

        // Unskewing factor for intSkewLoc to get to input space
        auto t = std::accumulate(skewed_coord.begin(), skewed_coord.end(), 0) * g;
        // skewed simplex origin unskewed to input space would be:
        // cellOrigin=[v-t for v in intSkewLoc]
        
        // Distance from unskewed simplex origin (intSkewLoc[i]-t) to loc,
        // all in input space
        std::vector<float> cell_dist;
        for(int i : d_range){
            cell_dist.push_back(coord[i] - skewed_coord[i] + t);
        }
        
        std::cout << "cell_dist " << cell_dist << "\n";

        // Indexs of items in cellDist, largest to smallest
        // To find correct vertexes of containing simplex, the containing hypercube
        // is traversed one step of +1 on each axis, in the order given
        // by greatest displacement from origin of hyper cube first.
        // This order is stored in distOrder: The order to traverse the axies
        auto dist_order = sort_with(d_range, cell_dist);
        std::reverse(dist_order.begin(), dist_order.end());

        std::cout << "dist_order " << dist_order << "\n";
        
        return 0.0f;
    }
 
    int hash(int seed){
        return seed;
    }
 
    int seed, d, f, g;
    float cornerToFaceSquared, valueScaler;
    std::vector<std::vector<float>> vecs;
};

int main(){
    simplex_noise s(0.0f, 5);
    s.noise({3,2,-1,3,8},false);
    
}