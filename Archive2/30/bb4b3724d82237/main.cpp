
#include <iostream>
using namespace std;

// Do not declare variables outside main() a.k.a "global variables"
// It is considered bad habit

int main()
{
    // always declare variables inside blocks "{ }"
    int nQuiz;   // number of quizzes
    int nAss;    // number of assignment
    double quiz = 0.0;
    double grade; // remember: if u don't assign a value to a variable
    double exam;  //           it's value is undefined. 
    double total;

    cout << "Prelim Grade"        << "\n"
         << "Enter How Many Quiz: ";
    cin >> nQuiz;

    cout << "Enter how many assignment: ";
    cin >> nAss;

    //
    // Get the quizzes
    //

    // DO NOT use this for loop format: for(int i = 1; i <= N; i++) { ... }
    // Use this instead               : for(int i = 0; i < N; ++i) { ... } ==> always start from zero
    for(int i = 0; i < nQuiz; ++i)
    {
        double temp;

        cout << "Enter quiz no " << i + 1 << ": ";
        cin >> temp;

        quiz += temp;
    }

    //
    // Do the same for the quizzes, attendance, etc...
    //


}