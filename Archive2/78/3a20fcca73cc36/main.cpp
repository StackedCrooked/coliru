#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;


class Database
{
    vector<double> dataStore;
public:
	Database(vector<double> v) : dataStore( move(v) ) {}
	double getKthSmallest(size_t k) const { return dataStore[k]; }
};


double findMedian(const Database& A, const Database& B, size_t N)
{
	int leftA = 0; int rightA = N; int middleA = leftA + (rightA - leftA - 1) / 2;
	int leftB = 0; int rightB = N; int middleB = leftB + (rightB - leftB) / 2;

	double medianLowerBound = numeric_limits<double>::min();
	double medianUpperBound = numeric_limits<double>::max();
	double currentA = A.getKthSmallest(middleA);
	double currentB = B.getKthSmallest(middleB);

	while (currentA > medianLowerBound && currentA < medianUpperBound &&
		currentB > medianLowerBound && currentB < medianUpperBound) {

		if (currentA < currentB) {
			medianLowerBound = currentA;
			medianUpperBound = currentB;
			leftA = middleA; rightB = middleB;
		}
		else {
			medianLowerBound = currentB;
			medianUpperBound = currentA;
			leftB = middleB; rightA = middleA;
		}

		middleA = leftA + (rightA - leftA - 1) / 2;
		middleB = leftB + (rightB - leftB) / 2;
		currentA = A.getKthSmallest(middleA);
		currentB = B.getKthSmallest(middleB);
	}

	return medianLowerBound + (medianUpperBound - medianLowerBound) / 2;
}


int main()
{
	vector<double> A = { 1, 2, 3, 4 };
	vector<double> B = { 5, 6, 7, 8 };

	cout << findMedian(B, A, A.size()) << endl;
    
    return 0;
}