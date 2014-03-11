#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int check_correct_answers ( char [], char [], char, double ); 
char print_student_grade( int score);


int main()
{
    ifstream inFile;
    ofstream outFile;
    inFile.open ("input");

    double score;
    char grade; 

    string header;
    string studentID;
    string studentAnswers;
    getline(inFile,header);
    
    cout<<"The correct answers are "<< header << endl<<endl;
    while(getline(inFile, studentID, ' '))
    {
        cout << studentID <<" ";
        getline(inFile, studentAnswers);
        cout << studentAnswers << endl;
    }
    return 0;
}
int check_correct_answers( char answerKey[], char studentAnswers[], int score, char grade)
{
    int i, correct = 0, incorrect = 0, blank = 0;
    for (i = 0; i < 23 - 1; i++)
    {
        if (answerKey[i] == studentAnswers[i])
            correct++;
        if (answerKey[i] != studentAnswers[i])
            incorrect++;
        if (studentAnswers[i] == ' ') 
        {
            blank++;
            incorrect--;
        }
        score = (correct * 5) + (incorrect * -2) + (blank * -4);
    }
    cout << score << endl;
    return score;
}

char print_student_grade( int score ) 
{
    int i;
    for (i = 0; i < 30; i++) 
    {
        if (score >= 90)
            cout<<"A"<<endl; 
        else if (score < 90 && score > 79)
            cout<< "B"<<endl;
        else if (score <= 79 && score > 69)
            cout<< "C"<<endl;
        else if (score <= 69 && score > 60)
            cout<< "D"<<endl;
        else if (score <= 59)
            cout<< "F"<<endl;
    }

    return 0;
}