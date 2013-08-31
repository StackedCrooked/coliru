#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int ac, char* av[])
{
    srand((unsigned int) time(0));

    {
        string reservior_name = "John";

        double capacity = 200;

        int max = 100;

        int min = 10;

        double inflow_range = max - min;

        double required = 18;
        if (required > 0.9 * (min + max) / 2)
        {
            cout << endl << "Warning: required ouflow is over 90% of the average inflow." << endl << "Returning to main menu ";
        }
        else
        {
            const int simulations = 10;
            int water_level = 0;
            int years = 1;
            cout << "Running simulation..." << endl;
            for (int i = 1; i <= simulations; i++)
            {
                int x = (rand() % (max - min + 1)) + min;
                
                cout << "X:" << x << endl;

                while (water_level < capacity)
                {
                    //double r = rand() * 1.0 / RAND_MAX;
                    //double x = min + inflow_range * r;
                    //int x = (rand()% (max-min + 1)) + min;
                    if (water_level + x > required)
                    {
                        water_level = water_level + x - required;
                    }
                    else
                    {
                        water_level = 0;
                    }
                    years++;

                }
                cout << "Simulation " << i << " took " << years << " years to finish" << endl;
            }
        }
    }
}