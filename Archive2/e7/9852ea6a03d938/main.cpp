#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

struct Line
{
    double slope;
	double offset;

	double evaluateAt(double x) const
	{
		return slope * x + offset;
	}
};

struct Polytope
{
	vector<Line> lines;
	vector<double> xcoords; //x intersections
};

double getIntersection_x(const Line& a, const Line& b)
{
	return (b.offset - a.offset) / (a.slope - b.slope);
}

bool polyBSurpassesPolyA(const Polytope& a, int aIndex, const Polytope& b, int bIndex, double x)
{
	const Line& aLine = a.lines[aIndex];
	const Line& bLine = b.lines[bIndex];
	return bLine.evaluateAt(x) - aLine.evaluateAt(x) > 0;
}

Polytope mergePolytopes(const Polytope& a, const Polytope& b)
{
	//Traverse the x coordinates of the polytopes' vertices in ascending order
	//to find the x coord where the B polytope surpasses the A polytope in y.
	unsigned int aIndex = 0; unsigned int bIndex = 0;
	while (aIndex != a.xcoords.size() && bIndex != b.xcoords.size()) {
		if (a.xcoords[aIndex] <= b.xcoords[bIndex]) {
			if (polyBSurpassesPolyA(a, aIndex, b, bIndex, a.xcoords[aIndex])) break;
			++aIndex;
		}
		else {
			if (polyBSurpassesPolyA(a, aIndex, b, bIndex, b.xcoords[bIndex])) break;
			++bIndex;
		}
	}

	//Finish off whichever vector still has values, if necessary
	while (aIndex != a.xcoords.size() && !polyBSurpassesPolyA(a, aIndex, b, bIndex, a.xcoords[aIndex])) ++aIndex;
	while (bIndex != b.xcoords.size() && !polyBSurpassesPolyA(a, aIndex, b, bIndex, b.xcoords[bIndex])) ++bIndex;
	
	//At this point, aIndex and bIndex represent the intersection of the two polytopes.
	//The following code links them together.
	Polytope result;

	//Protection against lines with same slope
	if (a.lines[aIndex].slope == b.lines[bIndex].slope) --aIndex; 

	result.lines.insert(end(result.lines), begin(a.lines), begin(a.lines) + 1 + aIndex);
	result.lines.insert(end(result.lines), begin(b.lines) + bIndex, end(b.lines));

	if (aIndex >= 0) {
		result.xcoords.insert(end(result.xcoords), begin(a.xcoords), begin(a.xcoords) + aIndex);
		result.xcoords.push_back(getIntersection_x(a.lines[aIndex], b.lines[bIndex])); //New intersection
	}
	result.xcoords.insert(end(result.xcoords), begin(b.xcoords) + bIndex, end(b.xcoords));

	return result;
}

Polytope getVisiblePolytope(const vector<Line>& lines, int left, int right)
{
	if (right - left == 1) return Polytope{ {lines[left]} }; //Polytope is just one line

	int middle = left + (right - left) / 2;
	auto leftPoly = getVisiblePolytope(lines, left, middle);
	auto rightPoly = getVisiblePolytope(lines, middle, right);

	return mergePolytopes(leftPoly, rightPoly);
}

vector<Line> removeHiddenLines(vector<Line>& lines)
{
	if (lines.size() <= 1) return lines;

	//Sort by slope in ascending order, break ties with offset
	sort(begin(lines), end(lines), [](const Line& a, const Line& b) {
		return a.slope == b.slope ? a.offset < b.offset : a.slope < b.slope;
	});

	return getVisiblePolytope(lines, 0, lines.size()).lines;
}


int main()
{
	vector<Line> lines = {
			{1, 0},
			{-1, 0},
			{0.5, 1.5},
			{-0.5, 1.5},
			{0, 1}
	};


	auto r = removeHiddenLines(lines);
    
    for (auto line : r) {
        cout << "y = " << line.slope << "x + " << line.offset << endl;   
    }

    return 0;
}