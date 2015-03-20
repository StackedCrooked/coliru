// stream includes
#include <iostream>
#include <fstream>
#include <sstream>

// data structures
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// etc
#include <type_traits>
#include <memory>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <regex>

int main()
{
    using Type = int; // milyen típusú számokkal számolunk.

    // beolvassuk az első, számokat tartalmazó sort, majd egy streambe helyezzük
    std::string line;
    std::getline(std::cin, line);
    std::stringstream numbers(line);

    // létrehozunk a könnyebb beolvasás és inicializás, illetve konstansság megtartása érdekében egy bemeneti iterátort
    std::istream_iterator<Type> input(numbers);

    // az első bemenetre nincs szükségünk.
    const Type countOfWordsDictionary = *++input,
               countOfBadWords = *++input;

    // létrehozzuk a szótárunkat
    std::vector< std::string > dictionary(countOfWordsDictionary);

    // feltöltjük a szótárunkat soronként beolvasva a bemenetről
    std::generate(dictionary.begin(), dictionary.end(), []()
    {
        std::string line;
        std::getline(std::cin, line);
        return line;
    });

    // kiiratjuk minden tesztesetre, hogy hány szótárbeli szóra hasonló
    std::generate_n(std::ostream_iterator<Type>(std::cout, "\n"), countOfBadWords, [&dictionary]()
    {
        // beolvassuk a bemeneti sort, majd kicseréljük a gömbölyű zárójeleket szögletesre,
        // hogy egy reguláris kifejezést kapjunk
        std::string line;
        std::getline(std::cin, line);
        std::replace(line.begin(), line.end(), '(', '[');
        std::replace(line.begin(), line.end(), ')', ']');
        std::cout << "regex:" << line << std::endl;
        std::regex badWord(line);

        // összeszámoljuk, hogy a szótárunkból mennyi illeszkedik a reguláris kifejezésre
        return std::accumulate(dictionary.begin(), dictionary.end(), 0, [&badWord](Type sum, std::string word)
        {
           return sum + std::regex_match(word, badWord);
        });
    });

    return 0;
}
