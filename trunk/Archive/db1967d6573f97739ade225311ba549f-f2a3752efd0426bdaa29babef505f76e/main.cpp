#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace variables
{
    vector<vector<int>> grid;
    vector<int> orderedNumbers;
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
    int xBound = currentGridPlacement[0] + nextPlacement[0];
    int yBound = currentGridPlacement[1] + nextPlacement[1];
    if      (xBound < 0 || xBound > (int)grid.at(0).size()) return true;
    else if (yBound < 0 || yBound > (int)grid.size()      ) return true;
    else                                                    return false;
}

vector<int> getValues(int movement[], int moveMagnitude)
{
    vector<int> values;
    for (int i = 1; i <= moveMagnitude; i++)
    {
        int nextCell[2] { (currentGridPlacement[0] + (movement[0] * i)), (currentGridPlacement[1] + (movement[1] * i)) };
        if (isOutOfBounds(nextCell)) 
        {
            cout << "OOB" << endl; 
            continue;
}
        values.push_back(grid.at(nextCell[0]).at(nextCell[1]));
    }
    return values;
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
    
    currentGridPlacement[0] = 1;
    currentGridPlacement[1] = 1;
    
    orderedNumbers.push_back(grid.at(currentGridPlacement[0]).at(currentGridPlacement[1]));
    cout << "done" << endl;
}

int main() 
{
    initialise();
    
    int totalNumbers = grid.size() * grid.at(0).size();
    cout << totalNumbers << " numbers in grid" << endl;
    while ((int)orderedNumbers.size() != totalNumbers)
    {
        cout << endl;
        cout << "Numbers in list: ";
        for (int x : orderedNumbers)
        {
            cout << x << ", ";   
        }
        cout << endl;
        if (MoveUp)
        {
            cout << "Moving up" << endl;
            vector<int> values = getValues(Up, moveMagnitude);
            for (int i : values) { orderedNumbers.push_back(i); }
            MoveUp = false;
            MoveLeft = true;
            setCurrentPlacement(Up, moveMagnitude);
        }
        else if (MoveDown)
        {
            cout << "Moving down" << endl;
            vector<int> values = getValues(Down, moveMagnitude);
            for (int i : values) { orderedNumbers.push_back(i); }
            MoveDown = false;
            MoveRight = true;
            setCurrentPlacement(Down, moveMagnitude);
        }
        else if (MoveLeft)
        {
            cout << "Moving left" << endl;
            vector<int> values = getValues(Left, moveMagnitude);
            for (int i : values) { orderedNumbers.push_back(i); }
            MoveLeft = false;
            MoveDown = true;
            ++moveMagnitude;
            cout << "Move magnitude increased to " << moveMagnitude << endl;
            setCurrentPlacement(Left, moveMagnitude);
        }
        else if (MoveRight)
        {
            cout << "Moving right" << endl;
            vector<int> values = getValues(Right, moveMagnitude);
            for (int i : values) { orderedNumbers.push_back(i); }
            MoveRight = false;
            MoveUp = true;
            ++moveMagnitude;
            cout << "Move magnitude increased to " << moveMagnitude << endl;
            setCurrentPlacement(Right, moveMagnitude);
        }
    }
    
    for (int x : orderedNumbers)
    {
        cout << x << ", ";   
    }
}