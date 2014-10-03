#include <iostream>
#include <cstring>
#include <map>

using namespace std;

const int array_size = 12;
string letter[array_size] = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"};
int percent [array_size] = {93, 90, 87, 83, 80, 77, 73, 70, 67, 63, 60, 60};
map <string, int> grades;

double score = 0;
string scale = "";

int main (void)
{
    
    cout << "What is the numeric grade? ";
	cin >> score;
	
	//Declare values to the grade variable
	for (int n = 0; n < array_size; n++)
	{
		grades[letter[n]] = percent[n];
	}
	
	//Determine the letter grade corresponding to the numerical grade inputted by the user
	for (int n = 0; n < array_size; n++)
	{
		if (score > percent[n])
		{
			cout << "\n\nThe corresponding letter grade to this numeric grade is: " << letter[n];
			break; //Once the score is found to be greater than the specified percent value, we have arrived at the correct letter grade and this loop's purpose is fulfilled.
		}
	}
	
	cout << "\n\nBy what method is this exam scaled? ";
	cin >> scale;
	
	double weight = 0;
	
    
    for(unsigned int i = 0; i < scale.length(); ++i) {
        scale[i] = tolower(scale[i]);
    }
    
	if (scale == "add")
	{
		cout << "\n\nHow many points are added to the numeric grade? ";
		cin >> weight;
		
		score += weight;
	}
	else if (scale == "proportion")
	{
		cout << "\n\nBy what percentage is the numeric grade increased? ";
		cin >> weight;
		
		score *= ((1+weight)*0.01);
	}
	else
	{
		cout << "This exam is not scaled. The final calculated grade is " << score << " ("  << letter << ")" << ". \n\n";
	}
	
} 