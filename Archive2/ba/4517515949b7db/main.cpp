#include <vector>
#include <iostream>

class Simple
{
public:
  Simple() : id(genId()) {}
  static int genId()
  {
    static int g_id = 0;
    return ++g_id;
  }
  int id;
};

typedef std::vector< std::vector<Simple> > SimpleGrid;

void printSimpleGrid(SimpleGrid& grid)
{
  for (std::size_t i = 0; i < grid.size(); i++) {
    for (std::size_t j = 0; j < grid[i].size(); j++) {
      std::cout << grid[i][j].id << " ";
    }
    std::cout << std::endl;
  }
}

int main()
{
  int dim = 3;
  SimpleGrid test(dim);
  for (int i = 0; i<dim; i++) {
    std::vector<Simple> row(dim);
    test[i] = row;
  }
  printSimpleGrid(test);
  return 0;
}