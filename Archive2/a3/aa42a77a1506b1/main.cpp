#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdlib>

// our movie class
class Movie
{
    // friend an ostream extraction operator for instances of Movie
    friend std::istream& operator >>(std::istream& inp, Movie& obj);

    // members variables here
    std::string title;
    
public:
    Movie() {}
    
    void load(std::istream& inp)
    {
        // TODO: load a movie here, **including title**
        if (std::getline(inp, title))
        {
            // ... other members ...
        }
    }
    
    // getters/setters here.
    const std::string& getTitle() const { return title; }
};


// friended extraction operator
std::istream& operator >>(std::istream& inp, Movie& obj)
{
    obj.load(inp); // loads movie from file.
    return inp;
}
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
    // pass movie file as first parameter to program
    if (argc < 2)
        return EXIT_FAILURE;
    
    // will hold our movie smart pointers
    std::ifstream inf(argv[1]);
    
    // load vector of movies.
    std::vector<Movie> movies {
        std::istream_iterator<Movie>(inf),
        std::istream_iterator<Movie>() };
    
    // vector loaded. use your movies
}
