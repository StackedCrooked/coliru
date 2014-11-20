#include <iostream>
#include <vector>

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in)
{
  double start = static_cast<double>(start_in);
  double end = static_cast<double>(end_in);
  double num = static_cast<double>(num_in);
  double delta = (end - start) / (num - 1);

  std::vector<double> linspaced(num - 1);
  for(int i=0; i < num; ++i)
    {
      linspaced[i] = start + delta * i;
    }
  linspaced.push_back(end);
  return linspaced;
}

void print_vector(std::vector<double> vec)
{
  for (double d : vec)
    std::cout << d << " ";
  std::cout << std::endl;
}

int main()
{
  std::vector<double> vec_1 = linspace(1, 10, 3);
  print_vector(vec_1);

  std::vector<double> vec_2 = linspace(6.0, 23.4, 5);
  print_vector(vec_2);
  return 0;
}

