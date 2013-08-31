// http://insanecoding.blogspot.com/2010/03/c-201x-variadic-templates.html

#include <iostream>
using namespace std;

//Since variadic templates are recursive, must have a base case
void output() { cout << '\n'; }

//Output function to output any type without type specifiers like printf() family
template <typename T, typename ...P>
void output(T t, P ...p)
{
  cout << t << ' ';
  if (sizeof...(p)) { output(p...); }
  else { cout << '\n'; }
}

//Since variadic templates are recursive, must have a base case
template <typename T>
T sum(T t) { return(t); }

//Compute sum of all parameters
template <typename T, typename ...P>
T sum(T t, P ...p)
{
  if (sizeof...(p))
  {
    t += sum(p...);
  }
  return(t);
}

//Test it
int main()
{
  output();
  output('5');
  output('5', 2);
  output('5', 2, "cows");
  output('5', 2, "cows", -1);
  output('5', 2, "cows", -1, 0.5f);
  output('5', 2, "cows", -1, 0.5f, 16.3);

  cout << endl;

  cout << sum(1) << '\n'
       << sum(1, 2) << '\n'
       << sum(1, 2, 3) << '\n'
       << sum(1, 2, 3, 4) << '\n'
       << sum(1, 2, 3, 4, 5) << '\n';

  cout << endl;

  cout << sum(0.1) << '\n'
       << sum(0.1, 0.2) << '\n'
       << sum(0.1, 0.2, 0.3) << '\n';

  cout << endl;

  return 0;
}
