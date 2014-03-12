#include <iostream>
#include <fstream>
#include <iomanip>
//#include "employee.h"

#ifndef HEADER_H
#define HEADER_H

#include <fstream>

using namespace std;

class employee
{
public:
void readData(ifstream & inf);

void Compute (int bp);

void print (ofstream & outf) const;

employee();

private:

int ID;
int Job_class;
int Years;
int Ed;
float sal;
};

#endif

using namespace std;

void employee ::readData(ifstream& inf)

{
inf >> ID >> Job_class >> Years >> Ed;