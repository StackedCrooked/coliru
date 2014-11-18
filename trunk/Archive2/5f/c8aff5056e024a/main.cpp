#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // rand -M 99 -n 20 -d '\n' -e > nums
    // cat nums | shuf | awk -- 'BEGIN { s = ""; } { s = s $1 ", "; } END { print s; }'
    // To są permutacje tego samego.
    std::vector <int> v1 { 49, 31, 4, 35, 50, 71, 44, 43, 88, 80, 64, 50, 75, 40, 86, 44, 59, 43, 5, 7 }; 
    std::vector <int> v2 { 44, 88, 75, 44, 59, 31, 71, 86, 5, 43, 43, 40, 80, 7, 50, 4, 35, 64, 50, 49 }; 
    std::vector <int> v3 { 4, 50, 88, 44, 50, 43, 75, 80, 71, 31, 7, 86, 35, 43, 49, 40, 44, 5, 59, 64 }; 
    std::vector <int> v4 { 86, 35, 44, 71, 50, 44, 59, 43, 31, 88, 75, 49, 80, 50, 5, 40, 4, 64, 7, 43 }; 
    std::vector <int> v5 { 4, 59, 75, 50, 43, 88, 31, 80, 64, 7, 86, 44, 49, 35, 5, 50, 44, 40, 71, 43 }; 
    std::vector <int> v6 { 64, 88, 71, 49, 75, 4, 35, 44, 43, 59, 7, 86, 43, 44, 5, 80, 50, 50, 31, 40 }; 
    std::vector <int> v7 { 5, 50, 7, 43, 88, 50, 35, 86, 4, 31, 44, 71, 49, 75, 59, 44, 80, 64, 40, 43 }; 

    typedef std::vector <int> Vector;
    std::vector <Vector *> vs { &v2, &v3, &v4, &v5, &v6, &v7 };

    for (Vector const *v : vs) {
        std::cerr << std::is_permutation (v1.cbegin (), v1.cend (), v->cbegin ()) << ", ";
    }
}
