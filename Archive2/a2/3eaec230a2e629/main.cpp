#include <iostream>
using namespace std;
int main ()
{
    int sum = 0;
	int count = 1;
	int num;
	{ while (count <= 10)
		cin >> num;
		sum = sum + num; 
		count++;
	}

	{ if (sum > 50)
		cout >> "the sum is high";
	}
		{ else cout >> "the sum is low";

		}
		
		
	return 0;
}