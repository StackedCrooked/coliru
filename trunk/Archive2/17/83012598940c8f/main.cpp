#include <iostream>
    
using namespace std;
    
int main() {
    char a[21], b[21];
    char yn = 'n';
    int ap = 0;
    int bp = 0;
    int set = 1;
    int tp = 0;
    char point;
    
    do {
        cout << "\t\t Beach VolleyBall Game Tracker" << endl << endl;
    
        cout << "Enter the name of Team A: ";
        cin >> a;
        cout << "Enter the name of Team B: ";
        cin >> b;
    
        cout << "Let the Games begin! Best 2 of 3 sets wins!" << endl << endl;
        // Above this point is looking good. Wont need to be repeated at all
        // anymore.
    
        for (int num = 7; num > tp;) {
            cout << " Current Status \t Set " << set << endl;
            cout << " Team A\t " << a << " | "
                << "Team B\t " << b << endl;
    
            cout << "\t " << ap << " | "
                << " \t " << bp << endl;
    
            cout << "What team scored a point (A or B)? ";
            cin >> point;
    
            if (point == 'A') {
                ap++;
                tp++;
            } else if (point == 'B') {
                bp++;
                tp++;
            }
        }
    
        cout << "Would you like to play again? (Y/N)? ";
        cin >> yn;
    } while (yn != 'n' && yn != 'N');
    
    return 0;
}
