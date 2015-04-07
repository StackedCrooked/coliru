#include <iostream>
#include <cstring>
#include <memory>
#include <cstring>
#include <vector>
using namespace std;

void passSomething(std::vector<int> vec)
{
    vec.push_back(5);   
}

int main(int argc, char *argv[])
{

   int *ptr;
   int temp[3] = {1, 2, 3};
   *temp = 5;
   ptr = *temp;
   std::cout << *ptr;
}
