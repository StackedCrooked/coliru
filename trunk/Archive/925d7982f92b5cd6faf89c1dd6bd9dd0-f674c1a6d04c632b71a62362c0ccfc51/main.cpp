#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace variables
{
    vector<vector<int>> grid;
    vector<int> orderedNumbers;
    int totalNumbers;
    int currentGridPlacement[2];
    int Up[2]    = {-1, 0};
    int Down[2]  = { 1, 0};
    int Left[2]  = { 0,-1};
    int Right[2] = { 0, 1};
    int moveMagnitude = 1;
    bool MoveUp = true, MoveDown = false, MoveLeft = false, MoveRight = false;
}

using namespace variables;

void setCurrentPlacement(int movement[], int moveMagnitude)
{
    currentGridPlacement[0] = currentGridPlacement[0] + (movement[0] * moveMagnitude);
    currentGridPlacement[1] = currentGridPlacement[1] + (movement[1] * moveMagnitude);
}

bool isOutOfBounds(int nextPlacement[])
{
    if      (nextPlacement[0] < 0 || nextPlacement[0] > (int)grid.size() - 1      ) return true;
    else if (nextPlacement[1] < 0 || nextPlacement[1] > (int)grid.at(0).size() - 1) return true;
    else                                                            				return false;
}

void storeValues(int movement[], int moveMagnitude)
{
    for (int i = 1; i <= moveMagnitude; i++)
    {
        int nextCell[2] { (currentGridPlacement[0] + (movement[0] * i)), (currentGridPlacement[1] + (movement[1] * i)) };
        if (isOutOfBounds(nextCell)) continue;
        orderedNumbers.push_back(grid.at(nextCell[0]).at(nextCell[1]));
    }
}

void initialise()
{
    cout << "Initialising...";
    int number = 1;
    int x = 3, y = 3;
    for (int i = 0; i < x; i++)
    {
        vector<int> line;
        grid.push_back(line);
        for (int j = 0; j < y; j++)
        {
            grid.at(i).push_back(number);
            ++number;
        }
    }
    totalNumbers = grid.size() * grid.at(0).size();
    currentGridPlacement[0] = 1;
    currentGridPlacement[1] = 1;
    
    if (!isOutOfBounds(currentGridPlacement)) orderedNumbers.push_back(grid.at(currentGridPlacement[0]).at(currentGridPlacement[1]));
    cout << "done" << endl;
}

int main() 
{
    initialise();
    
    cout << totalNumbers << " numbers in grid" << endl;
    while ((int)orderedNumbers.size() != totalNumbers)
    {
        if (MoveUp)
        {
            storeValues(Up, moveMagnitude);
            MoveUp = false;
            MoveLeft = true;
            setCurrentPlacement(Up, moveMagnitude);
        }
        else if (MoveDown)
        {
            storeValues(Down, moveMagnitude);
            MoveDown = false;
            MoveRight = true;
            setCurrentPlacement(Down, moveMagnitude);
        }
        else if (MoveLeft)
        {
            storeValues(Left, moveMagnitude);
            MoveLeft = false;
            MoveDown = true;
            setCurrentPlacement(Left, moveMagnitude);
            ++moveMagnitude;
        }
        else if (MoveRight)
        {
            storeValues(Right, moveMagnitude);
            MoveRight = false;
            MoveUp = true;
            setCurrentPlacement(Right, moveMagnitude);
            ++moveMagnitude;
        }
    }
    
    for (int x : orderedNumbers)
    {
        cout << x << ", ";   
    }
}