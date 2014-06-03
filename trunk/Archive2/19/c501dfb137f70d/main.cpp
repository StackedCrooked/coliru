#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Recipe {
public:
    Recipe(string name1,string author1) : name(name1),author(author1){};
    Recipe(const Recipe& recipe);
private:
    string name;
    string author;
};
Recipe::Recipe(const Recipe& recipe)=default;

int main() {
    vector<Recipe> recipes;
    int Id = 31;
    std::string name = "bla";
    ostringstream ss;
    ss << Id;
    Recipe recipe(name,ss.str());
    recipes.push_back(recipe);  
    cout << "Working\n";
}