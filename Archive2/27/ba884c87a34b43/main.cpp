// Aufgabe zur Lösung in der Übung
// Ein gültiger Name besteht aus zwei Wörtern, die durch ein Leerzeichen
// getrennt sind.
//
// Modifiziere die Funktion parseName so, dass bei einem gülitgen Namen ein
// Paar bestehend aus Vorname und Nachname zurückgegeben wird.
#include <algorithm>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
std::pair<std::string, std::string> parseName(const std::string& name)
{
    auto pos = name.find(' ');
    std::string nachname = name.substr(pos+1, name.length() - pos);
    
    if ( pos != std::string::npos && pos != 0 && pos < name.length()
         && nachname.find(' ') == std::string::npos ) {
        return std::pair<std::string, std::string> { name.substr(0, pos), nachname };
    }
    
    // auto pos = std::find(name.begin(), name.end(), ' ');
    throw std::invalid_argument("Argument '" + name + "' was not a name!");
}
void printName(const std::pair<std::string, std::string> name)
{
  std::cout << "Prename is: " << name.first
<< ", lastname is: " << name.second << "\n";
}
int main()
{
  std::string not_correct1{"This is not a name"};
  std::string correct{"Michel Steuwer"};
  std::string not_correct2{"ThisNeither"};
  try {
    printName( parseName(not_correct1) );
  } catch (std::invalid_argument& e) {
    std::cout << "Argument was invalid: " << e.what() << "\n";;
  }
  try {
    printName( parseName(correct) );
  } catch (std::invalid_argument& e) {
    std::cout << "Argument was invalid: " << e.what() << "\n";;
  }
  try {
    printName( parseName(not_correct2) );
  } catch (std::invalid_argument& e) {
    std::cout << "Argument was invalid: " << e.what() << "\n";;
  }
}