#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::map<int, std::set<std::string>> map_counter_to_perms;

std::set<std::string> find_permutations(int n)
{
    std::set<std::string> permutations;
    if (n == 0) { return permutations;}
    if (n == 1) { permutations.insert("01");  return permutations;}

    if (map_counter_to_perms[n-1].empty())
        map_counter_to_perms[n-1] = find_permutations(n-1);
        
    auto& sub_permutations = map_counter_to_perms[n-1];
    for (auto& s : sub_permutations)
    {
        std::string temp = "01" + s;
        permutations.insert(temp);
        temp = "0" + s + "1";
        permutations.insert(temp);
        
        if (n == 2)
           continue;

        temp = s + "01";
        permutations.insert(temp);
    }
    return permutations;
}


int main()
{
    std::set<std::string> perms;
    perms = find_permutations(4);
    for (auto s : perms)
       std::cout << s << "\n";
    std::cout << "finised";
}