#include <iostream>

using namespace std;

template <size_t size_y>
bool findEvenDegrees(bool mapArray[][size_y])
{
    bool returnValue;
    for (int x=0; x<size_y; x++)
    {
        int result = 0;
        for (int y=0; y<size_y; y++)
        {
            result = result + mapArray[x][y];
            //the line below causes the problem
            cout << mapArray[x][y] << "\t" << result << "\t" << x << endl;
        }
        if (result%2 == 1)
        {
            returnValue = false;
            break;
        }
    }
    if (returnValue== false)
    {
        return returnValue;
    }
    else
    {
        return true;
    }
}

int main()
{
    bool array1[][6] =
    {
        {false,true,true,false,false,false},
        {true,false,false,true,false,false},
        {true,false,false,true,false,false},
        {false,true,true,false,true,true},
        {false,false,false,true,false,true},
        {false,false,false,true,true,false}
    };
    bool array2[][8] =
    {
        {false,true,true,false,false,false,false,false},
        {true,false,false,true,false,false,false,false},
        {true,false,false,true,false,false,false,false},
        {false,true,true,false,true,false,false,false},
        {false,false,false,true,false,true,true,false},
        {false,false,false,false,false,true,false,true},
        {false,false,false,false,true,false,false,true},
        {false,false,false,false,false,true,true,false}
    };
    bool answer1 = findEvenDegrees(array1);
    bool answer2 = findEvenDegrees(array2);
    if (answer1 == true)
    {
        cout << "Array 1 has a even degree for every switch." << endl;
    }
    else
    {
        cout << "Array 1 has a odd degree for at least one switch." << endl;
    }
    if (answer2 == true)
    {
        cout << "Array 2 has a even degree for every switch.";
    }
    else
    {
        cout << "Array 2 has a odd degree for at least one switch.";
    }
    return 0;
}