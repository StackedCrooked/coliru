#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

// Structures to manage the dataflow of our problem

struct Sensor { // Holds one set of sensor readings and timestamp
    float atTime;
	float acc[3];
	float mag[3];
};
struct Euler {  // Holds a single set of Euler angles
	float roll;
	float pitch;
	float yaw;
};
struct SensorData { // Holds a list (array) of all sensor readings
	int len;
	Sensor* meas;
};
struct EulerData { // Holds a list (array) of all Euler angles
	int len;         // and the list of corresponding times
	float* times;
	Euler* angles;
};

// Prototype for functions which will load and
// process the data in our structures

SensorData readData(ifstream&);
Sensor readRecord(ifstream&);
EulerData processData(SensorData);
Euler processSensor(Sensor);
void writeResult(ofstream&, EulerData);

// main function
int main(void) {

	ifstream datFile("sensor.dat");
	ofstream outFile("angles.dat");

	if (datFile.is_open()) {
		// Well written code, with judicious choice of variable
		// and function names, is essentially self-documenting. . .
		SensorData flightData = readData(datFile);
		EulerData angleHist = processData(flightData);
		writeResult(outFile,angleHist);
		// Can now do other stuff with angleHist, if desired:
		// statistical analysis, whatever.  We'll stop here. . .
	}
	else {
		cout << "Error opening sensor data file." << endl;
	}

	return 0;

}

// Support functions

// Read all the data in file to array of Sensor structures
SensorData readData(ifstream& fin) {
	SensorData S;

	// Find out how many data records in file
	fin >> S.len;
	// Allocate and "attach" a correct amount of memory to S.meas
	S.meas = new Sensor[S.len];
	// Read in each data record and store in S.meas array
	for (int k=0;k<S.len;k++) S.meas[k] = readRecord(fin);
	return S;
}

// Process all the loaded data in Sensor array
// and produce a list of corresponding Euler angles
EulerData processData(SensorData S) {
	EulerData E;

	// Get length of dataset in S; will be same for E
	E.len = S.len;
	// Allocate and "attach" a correct amount of memory
	//  to E.times and E.angles
	E.times = new float[E.len];
	E.angles = new Euler[E.len];

	// Process each measurement to get angles and store these,
	// and associated measurement time, in the appropriate arrays
	for (int k=0;k<E.len;k++) {
		E.angles[k] = processSensor(S.meas[k]);
		E.times[k] = S.meas[k].atTime;
	}

	return E;
}
// Read a single line of data and store in appropriate
// parts of a Sensor Structure
Sensor readRecord(ifstream& fin) {
	Sensor sensor1;
	fin>>sensor1.atTime>>sensor1.acc[0]>>sensor1.acc[1]>>sensor1.acc[2]>>sensor1.mag[0]>>sensor1.mag[1]>>sensor1.mag[2];
	return sensor1;
}

// Turns the readings in a single Sensor structure into the
// equivalent angles and fills an Euler structure with the result
Euler processSensor(Sensor S) {
	Sensor S1;
	Euler e1;
	float magn,z[3];
	magn=sqrt(pow(S.acc[0],2)+pow(S.acc[1],2)+pow(S.acc[2],2));
	for (int i=0;i<=2;i++){
		S1.acc[i]=S.acc[i]/magn;
	}
	magn=sqrt(pow(S.mag[0],2)+pow(S.mag[1],2)+pow(S.mag[2],2));
	for (int i=0;i<=2;i++){
		S1.mag[i]=S.mag[i]/magn;
	}
	z[0]=S1.acc[1]*S1.mag[2]-S1.acc[2]*S1.mag[1];
	z[1]=S1.acc[2]*S1.mag[0]-S1.acc[0]*S1.mag[2];
	z[2]=S1.acc[0]*S1.mag[1]-S1.acc[1]*S1.mag[0];
	e1.roll=0-asin(S1.acc[0]);
	if (cos(e1.roll)==0){
		e1.pitch=0;
		e1.yaw=atan2(sin(e1.roll)*z[2],sin(e1.roll)*S1.mag[2]);
	}
	else{
		e1.pitch=atan2(S1.acc[1]/cos(e1.roll),S1.acc[2]/cos(e1.roll));
		e1.yaw=atan2(z[0]/cos(e1.roll),S1.mag[0]/cos(e1.roll));
	}
	return e1;
}

// Writes all the data in a list of Euler structures to the
// output file in a nicely formatted way
void writeResult(ofstream& fout, EulerData E) {
	for(int i=0;i<E.len;i++){
		fout << left << setw(10) << E.times[i];
		fout << left << setw(10) << E.angles[i].roll;
		fout << left << setw(10) << E.angles[i].pitch;
		fout << left << setw(10) << E.angles[i].yaw;
	}
}

