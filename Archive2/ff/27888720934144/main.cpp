#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std::placeholders;

#include <unordered_map>
#include <string>

struct flyer 
{
  flyer(int aId, const std::string& aBand): iId(aId), iBand(aBand) {}
  bool operator==(const flyer& a)const { return iId == a.iId; }
  int iId;
  std::string iBand;
};

struct hash_flyer 
{
  int operator()(const flyer& x) const 
  { return std::hash<int>()(x.iId) ^ std::hash<std::string>()(x.iBand); }
};

typedef enum t {
    ITEM = 0
} tEnum ;

int main()
{
    
    t e = (t) 5;
    
std::unordered_map< flyer, double, hash_flyer > m3;

flyer myBand(0, "Pennywise");
m3.insert(std::make_pair(myBand, 42.0));    		//inserts
m3[flyer(1, "Muse")] = 25.5; 		  		//inserts

std::cout << "flyers stored:" << m3.size() << std::endl;

for (auto it = m3.begin(); 
     it != m3.end(); ++it)
{
  std::cout << (*it).first.iBand << " value:" << it->second << std::endl;
}

m3.erase(myBand);					//removes

}

