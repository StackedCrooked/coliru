#include <string>
#include <vector>
#include <algorithm>

bool string_in_vector(const std::string &str,std::vector<std::string> &arr)
{
 return std::find(std::begin(arr),std::end(arr),str) != std::end(arr);
}

int main() {}