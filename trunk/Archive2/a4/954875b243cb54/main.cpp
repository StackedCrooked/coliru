#include <iostream>
#include <algorithm>
#include <fstream>
#include <functional>
#include <cstdlib>

const int employees = 10;

// read the salaries from a file
void readSalaries(std::istream &iss, double *salaries, int size) {
    
    for (double *p = salaries; p < salaries + size; ++p) {
        iss >> *p;
    }
}

// Compute and display the highest and lowest salaries.
void computeMinMax(const double *salaries, int size, double &min, double &max) {
    
}

//Compute and display the average of salaries.
void computeAverage(const double *salaries, int size) {
    
}

//Print all salaries.
void printSalaries(const double *salaries, int size) {
    
}

//Sort in decreasing order.
void sortSalaries(double *salaries, int size) {
    std::sort(salaries, salaries + size, std::greater<double>());
}

//Increase salaries according to user input percentage.
void bonus(double *salaries, int size, double bonusAmt) {
    
}


int displayMenu() {
    int selection;
    std::cout << "Select any of the following options:\n\n"
         << "1 - Compute and display the highest and lowest salaries.\n"
         << "2 - Compute and display the average of salaries.\n"
         << "3 - Print all salaries.\n"
         << "4 - Sort in decreasing order.\n"
         << "5 - Increase salaries according to user input percentage.\n"
         << "6 - Exit\n\n";
    std::cin >> selection;
    return selection;
}


int main()
{
    double max, min;
    bool exit = true;
	double salaries[employees] = {0};
    std::ifstream file("employees.txt");
    
    if (file.good()) {
        readSalaries(file, salaries, employees);
        exit = false;
    }
    
    printSalaries(salaries, employees);
    std::cout << std::endl;
    
    while (!exit) {
        switch(displayMenu()) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                std::cout << "Thank you for using our system☺ ☺☺ ☺\n\n";
                exit = true;
                break;
            default:
                std::cout << "Incorrect option...try again\n\n";
        }
    }

   return 0;
}