#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using Point = std::pair<int, int>;

#define LARGEUR_GRILLE 22
vector<Point> positions;

bool verifierNonPrise(Point const& emplacement) {
    return std::find_if(begin(positions), end(positions), [&emplacement](Point const& val){
        auto const delta1 = emplacement.first  - val.first;
        auto const delta2 = emplacement.second - val.second;
        return delta2 == 0 || delta2 == delta1 || delta2 == -delta1;                
    }) == end(positions);   
}

bool placerDame(int i) {
    for (int j = 1; j <= LARGEUR_GRILLE; ++j) {
        Point p(i, j);
        if (verifierNonPrise(p)) {
            positions.push_back(p);
            if (i == LARGEUR_GRILLE || placerDame(i + 1)) 
                return true;        
            positions.pop_back();
        }
    }
    return false;
}

int main()
{
    using std::chrono::system_clock; 

    system_clock::time_point begin_time = system_clock::now();
    positions.reserve(LARGEUR_GRILLE); 

    placerDame(1);
    for (auto const& point : positions)
        cout << "(" << point.first << "; " << point.second << ")" << endl;

    system_clock::time_point end_time = system_clock::now();

    long long elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
    cout << "Duration (milliseconds): "
         << elapsed_milliseconds
         << std::endl;    
}
