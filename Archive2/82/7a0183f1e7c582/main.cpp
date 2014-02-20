#include <vector>
#include <iostream>

std::vector<double> calculate(std::vector<double> values, std::vector<double> values2)
{
    std::vector<double> vel(2, 0);

    for(unsigned i=0; (i < values.size()); i++)
    {
        vel[i] = values[i] - values2[i];
    }

    return vel;
}

int main() {
  std::vector<std::vector<double> > values = { {5,8}, {3, 4}, {4, 4}, {2, 1}};

    std::vector<std::vector<double> > v;


    for(unsigned i=0; (i < values.size()-1); i+=2)
    {   
        v.push_back(calculate(values[i], values[i + 1]));
    }

    for(unsigned i=0; (i < v.size()); i++)
    {
        for(unsigned j=0; (j < v[i].size()); j++)
        {
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }
}