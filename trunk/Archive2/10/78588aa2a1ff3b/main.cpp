// A little calculator test

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <sstream>

using std::cout;
using std::cin;

int main()
{
    // Ignore this line, it's a hack so std::cin works
    std::istringstream ss("2\n2 3 4");
    cin.rdbuf(static_cast<std::istream&>(ss).rdbuf(cin.rdbuf()));
  cout << "Press 1 to add, 2 to multiply, 3 to subtract, 4 to divide, or 5 to exit: ";

  int input;
  cin >> input;
  std::cin.ignore();

  if (input != 5)
    {
      // Some variable declarations
      std::string numbers_str;
      std::vector<std::string> numbers_vect;
      std::string op_names[] = {"added", "multiplied", "subtracted", "divided"};

      cout << "Enter 2 or more numbers to be " << op_names[input - 1] << ": ";
      std::getline(cin, numbers_str);

      boost::split(numbers_vect, numbers_str, boost::is_any_of("\t "));
      std::vector<int> numbers_int(numbers_vect.size());

/*
      for (unsigned int i; i < numbers_vect.size(); i++)
        {
          numbers_int.push_back(std::stoi(numbers_vect[i]));
        }
*/
    std::transform(begin(numbers_vect), end(numbers_vect), begin(numbers_int), [](const std::string& val) { return std::stoi(val); });

      if (input == 1)
        {
          int sum = std::accumulate(numbers_int.begin(), numbers_int.end(), 0);
          cout << sum << std::endl;
        }
      else if (input == 2)
        {
           int multiply_ans = std::accumulate(numbers_int.begin(), numbers_int.end(), 1, std::multiplies<int>{}); /*1;
           for (unsigned int i = 1; i < numbers_int.size(); i++)
             {
               multiply_ans *= numbers_int[i];
             }*/
          cout << multiply_ans << std::endl;
        }
      else if (input == 3)
        {
          int subtract_ans = std::accumulate(numbers_int.begin()+1, numbers_int.end(), numbers_int[0], std::minus<int>{}); /*numbers_int[0];
          for (unsigned int i = 1; i < numbers_int.size(); i++)
            subtract_ans -= numbers_int[i];*/
          cout << subtract_ans << std::endl;
        }
      else
        {
          cout << "NIY" << std::endl;
        }
    }
  else
    {
      cout << "Invalid option \"" << input << "\"" << std::endl;
    }

    // Ignore this line
    cin.rdbuf(static_cast<std::istream&>(ss).rdbuf(cin.rdbuf()));
}
