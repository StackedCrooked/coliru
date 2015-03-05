#include <string>
#include <vector>
#include <fstream>

struct Entry 
{ 
    std::string origin_, dest_, airline_; 
	int price_, duration_; 
}; 

int main()
{
   std::vector<Entry> entries; 
   Entry e; 
   std::ifstream my_ifstream("data.txt");
   while (my_ifstream >> e.origin_ >> e.dest_ >> e.airline_ >> e.price_ >> e.duration_) 
       entries.push_back(e);
}