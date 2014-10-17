#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//function prototype
MovieData DisplayMovie(MovieData movie);

struct MovieData
{
    string  title,
            director;
    int     yearReleased;
    double  runningTime;
};


int main()
{
    MovieData movie1 = { "Almost Famous", "Cameron Crowe", 2003, 135.65 };
    MovieData movie2 = { "A River Runs Through It", "Robert Redford", 1993, 120.05 };
    cout << "My all time favorite movie" << endl;
        DisplayMovie(movie1);
        cout << "My second favorite movie is " << endl;
        DisplayMovie(movie2);

    return 0;
};


/**********************************
Function to display the movie data
***********************************/

MovieData DisplayMovie(MovieData movie)
{
    cout << "          " << movie.title << "             " << endl;
    cout << "written by " << movie.director << " in " << movie.yearReleased << endl;
    cout << "had a running time of " << movie.runningTime << " minutes. " << endl;

}    