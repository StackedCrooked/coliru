/* 
 * File:   main.cpp
 *
 * Created on January 1, 2015, 9:58 PM
 */

#include <cstdlib>
#include <vector>
#include <set>
#include <cassert>
#include <iostream>

using namespace std;

typedef std::vector<int> Perm;
 
  class Comparator{
    public:
        /**
         * comparator for storing permutations in a set, maps the comparison to
         * int comparison
         * @param p1
         * @param p2
         * @return 
         */
        bool operator()(const Perm &p1, const Perm &p2) const{
            assert(p1.size() == p2.size());
            for(int i = 0; i != p1.size(); i++){
                if(p1[i] < p2[i])
                    return true;
            }
            return false;
        }
    };
    
//Using a set guarantees uniqueness
std::set<Perm, Comparator> population;

void count(){
    std::cout<<"official size:"<<population.size()<<std::endl;
    int counter = 0;
    for(Perm p : population)
        counter++;
    std::cout<<"real size:"<<counter<<std::endl;
    assert(counter == population.size());
}

int main(int argc, char** argv) {
    
    std::vector<Perm> tmpPop;
    //Length of two will work.
    tmpPop.push_back(Perm({10,8,7}));
    tmpPop.push_back(Perm({0,7,10}));
    tmpPop.push_back(Perm({0,7,10}));
    
    
    population.insert(tmpPop.begin(), tmpPop.end());
    count();
    return 0;
}

