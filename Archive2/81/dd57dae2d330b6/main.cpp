#include <iostream>
#include <string>
using namespace std;

struct car{
    int weight;
    string color;
    friend ostream &operator << (ostream &, const car &);
};

ostream &operator << (ostream &oss, const car &myCar) {
    oss << "Weight = " << myCar.weight << ", Color = " << myCar.color;
	return oss;
}
    
int main()
{
	car car1 = {100, "red"};
	car car2 = {200, "blue"};
	car car3 = {300, "green"};

	car *pc1, *pc2, *pc3;
	pc1 = &car1;
	pc2 = &car2;
	pc3 = &car3;
	cout << pc1 << endl;
	cout << &pc1 << endl;
	cout << (*pc1) << endl << endl;
	cout << (*pc1).weight << " " << pc1->color << endl;
	cout << (*pc2).weight << " " << pc2->color << endl;
	cout << (*pc3).weight << " " << pc3->color << endl;

   return 0;
}
