#include <cassert>
#include <string>
 #include<iostream>
int main()
{
    std::string s{ "Exemplar\n" };
    std::string::size_type const capacity = s.capacity();
 std::cout<<s;
    s.clear();

    std::cout<<"check\n"<<s;
   // assert(capacity == s.capacity());
 //   assert(s.empty());
 //   assert(0 == s.size());
}