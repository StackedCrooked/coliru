#include <array>
#include <iostream>
#include <utility>

void print(std::array<int, 5>& array)
{
  for(int i: array)
    std::cout << i << " ";
  std::cout << std::endl;
}

int main()
{
  std::array<int, 5> seq = {5, 1, 4, 2, 8};
  std::cout << "Start: ";
  print(seq);

  for (std::size_t i=0; i < seq.size(); ++i)
  {
    for (std::size_t j=i+1; j < seq.size(); ++j)
    {
      std::cout << "index: " << i << "," << j << "; "
                << "element: " << seq[i] << "," << seq[j] << "; ";

      if (seq[i] > seq[j])
        std::swap(seq[i], seq[j]);
    
      print(seq);
    }
    std::cout << "-- next iteration --" << std::endl;
  }
  std::cout << "End: ";
  print(seq);
}