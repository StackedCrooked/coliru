#include <sstream>

#include <string>
#include <iostream>

const std::string file_contents = "12,34.567.89\n,1.22.333";

int main()
{
  std::istringstream data(file_contents);
  std::string line;
  while(std::getline(data, line)) // #include <string>
  {
    std::string::size_type prev_index = 0;
    std::string::size_type index = line.find_first_of(".,");
    while(index != std::string::npos)
    {
      std::cout << line.substr(prev_index, index-prev_index) << '\n';
      prev_index = index+1;
      index = line.find_first_of(".,", prev_index);
      std::cout << "prev_index: " << prev_index << " index: " << index << '\n';
    }
    std::cout << line.substr(prev_index, line.size()-prev_index) << '\n';
  }
}
