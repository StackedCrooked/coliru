#include <vector>
#include <iostream>
using namespace std;

class Workshop
{
public:
    int pictureFrames( vector<int> pieces );
};

int Workshop::pictureFrames( vector<int> pieces )
{
    int count = 0;

    for ( int i = 0 ; i < pieces.size() - 2 ; i++ )
    {
        for ( int j = i + 1; j < (pieces.size() - 1) ; j++ )
        {
            for ( int k = j + 1; k < (pieces.size()); k++ )
            {
                bool possible = (pieces[i] + pieces[j] > pieces[k]) &&
                                (pieces[j] + pieces[k] > pieces[i]) &&
                                (pieces[k] + pieces[i] > pieces[j]);
                if ( possible )
                    count++;
            }
        }
    }
    return count;
}

void main()
{
    Workshop w;
    vector<int> pieces;
    pieces.push_back( 100 );
    w.pictureFrames( pieces );
}