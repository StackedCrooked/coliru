#include <iostream>
#include <cstring>
#include <map>

using namespace std;

const int array_size = 12;
string letter [array_size] = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"};
int percent [array_size] = {93, 90, 87, 83, 80, 77, 73, 70, 67, 63, 60, 0};

double score = 0;
bool choice = false;
string scale = "";

string findLetterGrade (double score, int array_size)
{
    string letter_grade = "";
	
	for (int n = 0; n < array_size; ++n)
	{
		if (score > percent[n])
		{
			letter_grade = letter[n];
		    break; //Once the score is found to be greater than the specified percent value, we have arrived at the correct letter grade and this loop's purpose is fulfilled
		}
	}
	return letter_grade;
} 

int main (void)
{
    cout << "What is the numeric grade? ";
	cin >> score;
	
	//Determine the letter grade corresponding to the numerical grade inputted by the user
	cout << "\n\nThe corresponding letter grade to this numeric grade is: " << findLetterGrade(score, array_size);
	
	cout << "\n\nWould you like this exam to be scaled? ";
	cin >> choice;
	if (choice)
	{
		cout << "\n\nBy what method is this exam scaled? ";
		cin >> scale;	
	}
	
	for(unsigned int n = 0; n < scale.length(); ++n) 
	{
		scale[n] = tolower(scale[n]);
    }
	
	double weight = 0;
	
	if (scale == "add")
	{
		cout << "\n\nHow many points are added to the numeric grade? ";
		cin >> weight;
		
		score += weight;
		
		cout << "\n\nThe corresponding letter grade to this scaled numeric grade is: " << findLetterGrade(score, array_size);
	}
	else if (scale == "proportion")
	{
		cout << "\n\nBy what percentage is the numeric grade increased? ";
		cin >> weight;
		
		score *= ((1+weight)*0.01);
		
		cout << "\n\nThe corresponding letter grade to this scaled numeric grade is: " << score;
	}
	else
	{
		cout << "\n\nThis exam is not scaled. The final calculated grade is " << score << " ("  << findLetterGrade(score, array_size) << ")" << ". \n\n";
	}
	
	return 0;
}

