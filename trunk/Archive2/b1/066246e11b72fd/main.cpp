#include <iostream>
#include <string> 

using namespace std;

struct GameType {
    std::string gameName;
    int gameRating;
    int gameSales;
};

void AddGameData(GameType list[], int& totalRead);
void DisplayAllGames(GameType *list, int n);

int main(){
int totalRecords = 4;
GameType gameList[20] = {{"Game 1", 1, 100}, {"Game 2", 2, 200}, {"Game 3", 3, 300}, {"Game 4", 4, 400}, {"Game 5", 5, 500}};

//Populate arrays with data

//Display menu

//If the user enters an invalid option, prompt them again
char input = 'A'; //Default value (initialize)

while(input != 'X')
{
    cin >> input;
    switch(input)
    {
        case('A'):
            DisplayAllGames(gameList, totalRecords);
            cout << endl;
            break;
        case('B'):
            AddGameData(gameList, totalRecords);
            cout << endl;
            break;
                    case('X'):
                            break;
    };
};
}

void AddGameData(GameType list[], int& totalRead){

totalRead++; //New item in the arrayStruct

//cout << "Add new game data:" << endl;
//cout << "Title Name: ";
cin >> list[totalRead].gameName;
//cout << "\nGame Rating: ";
cin >> list[totalRead].gameRating;
//cout << "\nGame Sales: ";
cin >> list[totalRead].gameSales;
//cout << "Record added." << endl;
}

void DisplayAllGames(GameType *list, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << list[i].gameName << '\n';   
        std::cout << list[i].gameRating << '\n';
        std::cout << list[i].gameSales << '\n';
    }
}