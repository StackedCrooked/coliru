#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

struct Pair
{
   int x,y;
   friend bool operator==(Pair a, Pair b)
   {
     return a.x == b.x && a.y == b.y;
   }
   friend istream& operator>>(istream& is, Pair& a)
   {
     is >> a.x >> a.y;
     return is;
   }
   friend ostream& operator<<(ostream& os, Pair a)
   {
     os << '(' << a.x << ',' << a.y << ')';
     return os;
   }
};

using Pairs = vector<Pair>;

int main()
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);

        unsigned n;
        Pairs pairs;

        if (iss >> n)
        {
            copy_n(istream_iterator<Pair>(iss), n, back_inserter(pairs));
        } 
        if (!iss)
            return 255;

        std::cout << "Read a line with " << n << " pairs (check: " << pairs.size() << ")\n";
    }
}
