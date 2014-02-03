#include <iostream>
#include <list>
#include <functional>

class Song {
public:
    std::string title;
    double length;
    
    Song(std::string title, double length) : title(std::move(title)), length(length) { }
};

class Cd {
    std::list<std::reference_wrapper<Song>> songs;
    std::string performer, title;
    
public:
    void addSong(Song & s) {
        songs.push_back(std::ref(s));
    }
    void removeSong(unsigned n) {
        auto it = songs.begin();
        std::advance(it, n);
        songs.erase(it);
    }
    void report() {
        std::cout << title << ", " << performer << '\n';
        for (auto const& song : songs) {
            std::cout << song.get().title << " " << song.get().length << '\n';
        }
        std::cout << std::endl;
    }
    
    Cd(std::string performer, std::string title) :
        performer(std::move(performer)), title(std::move(title))
    { }
};

int main() {

    Song s1("Hey Jude", 4.52);
    Song s2("The song of Pie", 3.14);
    
    Cd c1 ("Beatles", "Capitol");
    c1.addSong(s1);
    c1.addSong(s2);
    c1.report();
    
    //c1.removeSong(s1);
    c1.removeSong(0);
    c1.report();
    
}
