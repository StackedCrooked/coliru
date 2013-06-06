#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

void SemiMinor(int planet, double starMass, double planetVelo[][2], double point[], double G);

int main()
{
    //Declaring Variables
    const int maxPlanet = 20;
    double point[2];
    double axis[maxPlanet][2] = {0};
    const double G = 6.6738e-11;
    double starMass;   // Kg
    string starName;
    string planetName[maxPlanet];
    double planetAp[maxPlanet]; // meter
    double planetVelo[maxPlanet][2] = {0}; //m/s

    //Read in Variables
    int planetNum = 0;
    string line;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        getline (myfile,line);
        starName = line;
        getline (myfile,line);
        starMass = atof(line.c_str());
        for (int i=0; i<5; i++)
            getline (myfile,line);
        while ( myfile.good() )
        {
            getline (myfile,line);
            planetName[planetNum] = line;
            getline (myfile,line);
            planetAp[planetNum] = atof(line.c_str());
            getline (myfile,line);
            planetVelo[planetNum][1] = atof(line.c_str());
            getline (myfile,line);
            planetNum++;
        }
        myfile.close();
    }
    //Find Ellipse
    for (int i=0; i<planetNum; i++)
    {
        point[2] = {0};
        point[0] = planetAp[i];
        axis[i][0] = point[0];
        cout << planetName[i] << "\t" << planetAp[i] << "\t" << planetVelo[i][1] << endl;
        SemiMinor(i, starMass, planetVelo, point, G);
        axis[i][0] -= point[0];
        axis[i][1] = point [1];
    }
    //Print to file
    ofstream myfile2;
    myfile2.open ("Output.txt");
    myfile2 << "\t\t" << starName << "\t\t";
    for (int i=0; i<planetNum; i++)
        myfile2 << planetName[i] << "\t\t";
    myfile2 << "\n\t\t\t\t";
    for (int i=0; i<planetNum; i++)
        myfile2 << planetAp[i]-axis[i][0] << "\t\t";
    myfile2 << "\n\t\t\t\t";
    for (int i=0; i<planetNum; i++)
        myfile2 << axis[i][0] << "\t\t";
    myfile2 << "\n\t\t\t\t";
    for (int i=0; i<planetNum; i++)
        myfile2 << axis[i][1] << "\t\t";
    myfile2.close();

    return 0;
}

//Find SemiMinor Axis
void SemiMinor(int planet, double starMass, double planetVelo[][2], double point[], double G)
{
    double deltaT = 86400; //seconds
    double position[2][2]={0};
    double vx = planetVelo[planet][0];
    double vy = planetVelo[planet][1];
    position[1][0] = point[0];
    int i = 0;
    double a, ax, ay;
    do
    {
        position[0][0] = position[1][0];
        position[0][1] = position[1][1];
        cout << i << "\t" << position[0][0] << "\t" << position[0][1] << endl;
        i++;
        a = G * starMass / pow(sqrt(pow(position[0][0],2)+pow(position[0][1],2)),3);
        ax = a*-position[0][0];
        vx += ax*deltaT;
        position[1][0] = position[0][0] + vx*deltaT + 0.5*ax*ax*deltaT;
        a = G * starMass / pow(sqrt(pow(position[0][0],2)+pow(position[0][1],2)),3);
        ay = a*-position[0][1];
        vy += ay*deltaT;
        position[1][1] = position[0][1] + vy*deltaT + 0.5*ay*ay*deltaT;
    }while (position[0][1] < position[1][1]);
    point[0] = (position[0][0]+position[1][0])/2;
    point[1] = max(position[0][1],position[1][1]);
    return;
}
