// vector::push_back
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector{1, 2, 3};
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    myvector.push_back (myint);
  } while (myint);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  return 0;
}