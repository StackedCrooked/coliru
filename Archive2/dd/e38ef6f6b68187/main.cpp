#include <iostream>
#include <vector>
#include <functional>
#include <memory>

using namespace std;

struct Epoch    { double t; };
struct Duration { double t; };

struct Note     { uint8_t pitch; Duration t; };
struct Tune     { std::vector<Note> notes; };

void tweet (const Tune & tune) 
{   for (auto n : tune.notes) 
    {   cout << "n.pitch : " << (int)n.pitch << endl;   }   }

int main()
{
    vector<Note> my_notes;
    Duration     my_first_note_duration { 3.14159 };
    Note         my_first_note { 42, my_first_note_duration };
    
    my_notes.push_back (my_first_note);
    tweet (Tune { my_notes });
}
