#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Coordinates
{    
    Coordinates(int x = 0, int y = 0)
    : _x{x}, _y{y}
    {
    }
    
    friend Coordinates operator-(const Coordinates& lhs, const Coordinates& rhs);
    friend Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs);
    
    bool isAnyCoordinateNegative() const
    {
        return (_x < 0) || (_y < 0);
    }

    int _x;
    int _y;
};

Coordinates operator-(const Coordinates& lhs, const Coordinates& rhs)
{
    return Coordinates{lhs._x - rhs._x, lhs._y - rhs._y};
}

Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs)
{
    return Coordinates{lhs._x + rhs._x, lhs._y + rhs._y};
}

template<unsigned int N, unsigned int M>
struct Matrix
{
    Matrix()
    : _2dArray{
                {1,1,1,2,3,3},
                {1,1,2,3,3,3},
                {1,2,2,2,2,2},
                {3,3,3,3,3,3}
              }
    {}
    
    int& operator[](const Coordinates& coordinates)
    {
        if (coordinates._x >= int(N) || coordinates._x < 0 || coordinates._y >= int(M) || coordinates._y < 0)
        {
            throw out_of_range{""};
        }
        
        return _2dArray[coordinates._x][coordinates._y];
    }
    
    void print() const
    {
        for (unsigned int x = 0; x != N; ++x)
        {
            for (unsigned int y = 0; y != M; ++y)
            {
                cout << _2dArray[x][y] << ", ";
            }
         
            cout << endl;
        }
    }
    
    int _2dArray[N][M];  
};

const unsigned int X_DIM = 4;
const unsigned int Y_DIM = 6;

Matrix<X_DIM, Y_DIM> countryMap;

typedef int CountryId;

std::unordered_map<CountryId, Coordinates> newCountries;

void findNeighbours(const Coordinates& reference, vector<Coordinates>& neighbours)
{
    static const Coordinates N{0,1};
    static const Coordinates NE{1,1};
    static const Coordinates E{1,0};
    static const Coordinates SE{1,-1};
    static const Coordinates S{0,-1};
    static const Coordinates SW{-1,-1};
    static const Coordinates W{-1,0};
    static const Coordinates NW{-1,1};
    
    neighbours.push_back(reference + N);
    neighbours.push_back(reference + NE);
    neighbours.push_back(reference + E);
    neighbours.push_back(reference + SE);
    neighbours.push_back(reference + S);
    neighbours.push_back(reference + SW);
    neighbours.push_back(reference + W);
    neighbours.push_back(reference + NW);
}

void paintCountry(CountryId countryId, const Coordinates& toPaint, int paint)
{
    if (countryMap[toPaint] == countryId)
    {
        // Paint
        countryMap[toPaint] = paint;

        // Find neighbours
        vector<Coordinates> neighbours;
        findNeighbours(toPaint, neighbours);
        // Call this method for all neighbours
        for (const auto& neighbour : neighbours)
        {
            try
            {
                paintCountry(countryId, neighbour, paint);
            }
            catch(...)
            {
                // ignore
            }
        }
    }
    else if (countryMap[toPaint] == paint)
    {
        // do nothing
    }
    else
    {
        // Other country, put on newCountries if it isn't there already
        if (newCountries.count(countryMap[toPaint]) == 0)
        {
            newCountries[countryMap[toPaint]] = toPaint;
        }
    }
}

int main()
{
    // I'm assuming 0 isn't on the matrix. If I cannot assume this I would do a first pass on the matrix to find a min-1 or max+1 value
    int paint = 0;
    
    // Put the first country on the countries to search for
    newCountries.insert({countryMap[{0,0}], {0,0}});
    
    unsigned int numberOfCountries = 0;
    
    while(newCountries.begin() != newCountries.end())
    {
        CountryId countryId = newCountries.begin()->first;
        Coordinates coordinates = newCountries.begin()->second;
        
        paintCountry(countryId, coordinates, paint);
        countryMap.print();
        cout << endl;
        newCountries.erase(countryId);
        
        ++numberOfCountries;
    }

    cout << "The number of countries is: " << numberOfCountries << endl;

    return 0;
}

