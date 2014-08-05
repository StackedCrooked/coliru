#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <chrono>
#include <algorithm>

using namespace std;

typedef std::pair<int, int>   Point;

#define LARGEUR_GRILLE 22
vector<Point> positions;


bool verifierNonPrise(Point const& emplacement) {
    return std::find_if(positions.begin(), positions.end(), [&emplacement](Point const& val){
        if (val.first != emplacement.first) {
            if ((val.second == emplacement.second) || (abs(val.second - emplacement.second) == abs(val.first - emplacement.first))) {
                return true;
            }
        }
        return false;
    }) == positions.end();
}

bool placerDame(int i) {
    bool bonnePosition = false;

    for (int j = 1; j <= LARGEUR_GRILLE && !bonnePosition; j++) {
        Point emplacement(i,j);
        positions.push_back(emplacement);
        if (verifierNonPrise(emplacement) && (i == LARGEUR_GRILLE || placerDame(i + 1))) {
            bonnePosition = true;
        }
        else {
            positions.pop_back();
        }
    }

    return bonnePosition;
}


int main()
{
    using std::chrono::system_clock;

    system_clock::time_point begin_time = system_clock::now();

    int i = 1;
    placerDame(i);
    for (vector<Point>::iterator it = positions.begin(); it!= positions.end(); it++) {
        cout << "(" << it->first << "; " << it->second << ")" << endl;
    }

    system_clock::time_point end_time = system_clock::now();

    long long elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
    cout << "Duration (milliseconds): "
         << elapsed_milliseconds
         << std::endl;    
}