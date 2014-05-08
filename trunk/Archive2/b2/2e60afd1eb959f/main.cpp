#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct Question {
    string question;
    string options[3];
    char answer;
};

bool isVowel( char c ) { return (c=tolower(c)) == 'a' || c == 'e' || c == 'i' || c =='o' || c == 'u'; }

int main()
{
    vector<Question> questions =
    {
        { "What is blue", { "Fruit", "Color", "Drink" }, '2' },
        { "What is a Ferrari", { "Car", "Animal", "Computer" }, '1' },
        { "What is Programming", { "Art", "...", "None of The Above" }, '2' } 
        // ...
    };
 
    random_shuffle( questions.begin(), questions.end() );
    
    string input = "placeholder";
    
    for( size_t i = 0; i < questions.size(); ++i )
    {
        cout << "Question " << i + 1 << " " << questions[i].question << '\n';
        
        for( size_t j = 0; j < 3; ++j ) // print the options
            cout << j+1 << ") " << (isVowel(questions[i].options[j][0]) ? "An " : "A ") << questions[i].options[j] << '\n';   
    
        cout << endl;
        // ...
    }
    
    return 0;
}
