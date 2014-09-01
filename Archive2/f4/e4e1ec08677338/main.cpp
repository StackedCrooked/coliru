#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>

// our movie class
class Movie
{
    // friend an ostream extraction operator for instances of Movie
    friend std::istream& operator >>(std::istream& inp, Movie& obj)
    {
        obj.load(inp); // loads movie from file.
        return inp;
    }

    // members variables here
    std::string title;
    
public:
    Movie() {}
    
    void load(std::istream& inp)
    {
        // TODO: load a movie here, **including title**
    }
    
    // getters/setters here.
    const std::string& getTitle() const { return title; }
};


int main(int argc, char *argv[])
{
    // pass movie file as first parameter to program
    if (argc < 2)
        return EXIT_FAILURE;
    
    // will hold our movie smart pointers
    std::vector<std::unique_ptr<Movie>> movies;
    
    std::ifstream inf(argv[1]);
    for (Movie movie; inf >> movie;)
        movies.emplace_back(new Movie(movie));
    
    // vector now loaded with movies from our input file.
    inf.close();
    
    // TODO: whatever you want with your movies.
}
