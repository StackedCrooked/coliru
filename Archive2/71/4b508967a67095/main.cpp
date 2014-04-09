#include <iostream>

using namespace std;

class CalcHorizonLine {

private:
    float line1[3], line2[3];
	float vanishingPoint1[3], vanishingPoint2[3], horizonLine[3];

public:
	CalcHorizonLine(float *coordinates, float *target);
	~CalcHorizonLine(void);
};

CalcHorizonLine::CalcHorizonLine(float *coordinates, float *target) {

    //START HORIZONTAAL//
	line1[0] = coordinates[1] - coordinates[3];
	line1[1] = coordinates[2] - coordinates[0];
	line1[2] = (coordinates[0]*coordinates[3]) - (coordinates[2]*coordinates[1]);

	line2[0] = coordinates[5] - coordinates[7];
	line2[1] = coordinates[6] - coordinates[4];
	line2[2] = (coordinates[4]*coordinates[7]) - (coordinates[6]*coordinates[5]);

	vanishingPoint1[0] = line1[1]*line2[2] - line2[1]*line1[2];
	vanishingPoint1[1] = line2[0]*line1[2] - line1[0]*line2[2];
	vanishingPoint1[2] = line1[0]*line2[1] - line2[0]*line1[1];
	//EINDE HORIZONTAAL//

	//START VERTICAAL//
	line1[0] = coordinates[1] - coordinates[5];
	line1[1] = coordinates[4] - coordinates[0];
	line1[2] = (coordinates[0]*coordinates[5]) - (coordinates[4]*coordinates[1]);

	line2[0] = coordinates[3] - coordinates[7];
	line2[1] = coordinates[6] - coordinates[2];
	line2[2] = (coordinates[2]*coordinates[7]) - (coordinates[6]*coordinates[3]);

	vanishingPoint2[0] = line1[1]*line2[2] - line2[1]*line1[2];
	vanishingPoint2[1] = line2[0]*line1[2] - line1[0]*line2[2];
	vanishingPoint2[2] = line1[0]*line2[1] - line2[0]*line1[1];
	//EIDNE VERTICAAL//

	//START sdfksdfj//
	horizonLine[0] = (vanishingPoint1[1] * vanishingPoint2[2]) - (vanishingPoint2[1] * vanishingPoint1[2]); 
	horizonLine[1] = (vanishingPoint2[0] * vanishingPoint1[2]) - (vanishingPoint1[0] * vanishingPoint2[2]);
	horizonLine[2] = (vanishingPoint1[0] * vanishingPoint2[1]) - (vanishingPoint2[0] * vanishingPoint1[1]);

	horizonLine[0] /= horizonLine[2];
	horizonLine[1] /= horizonLine[2];
	horizonLine[2] /= horizonLine[2];
	//EINDE dfsfdfd//

	target[0] = horizonLine[0];
	target[1] = horizonLine[1];
	target[2] = horizonLine[2];

}

CalcHorizonLine::~CalcHorizonLine(void) {
}


int main() {
    std::cout << "It's a kind of magic!" << std::endl;
}