#include<iostream>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<iterator>
#include<utility>
int main()
{
   std::map<int, std::string> mymap;
   std::set<int> myset;
   
   mymap[0] = "Tony";
   mymap[1] = "Bony";
   
   myset.insert(1);
   myset.insert(1);
   myset.insert(2);
   
   std::copy(myset.begin(), myset.end(), std::ostream_iterator<int>(std::cout, " "));
   //What should the type of ostream_iterator<???> be?
   std::copy(mymap.begin(), mymap.end(), std::ostream_iterator<std::pair<const int, std::string>>(std::cout, " "));
}