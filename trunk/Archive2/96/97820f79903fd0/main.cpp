#include <iostream>
#include <string>
#include <vector>

class cGeoPos {
    private:
        double lang;
        double breit;
    public:
        cGeoPos(double lang_in = 8.7, double breit_in = 52.5) 
            : lang(lang_in), breit(breit_in)
        { }
        
        friend std::ostream& operator<<(std::ostream& os, cGeoPos const& posi) {
            return os << "(" << posi.lang << ", " << posi.breit << ")";
        }

        friend std::istream& operator>>(std::istream& is, cGeoPos& posi) {
            return is >> posi.lang >> posi.breit;
        }
};

class cBaum {
    friend int main();
    private:
        std::string art;
        double hoch;
        cGeoPos posi;
    public:
        cBaum(std::string art = "-", double hoch = 0, double lang = 0, double breit = 0)
            : art(art), hoch(hoch), posi(lang, breit)
        { }

        bool valid() const { return art != "-"; }

        friend std::ostream& operator<<(std::ostream& os, cBaum const& baum) {
            return os << "[ '" << baum.art << "', Hőhe:" << baum.hoch << ", posi:" << baum.posi << " ]";
        }

        friend std::istream& operator>>(std::istream& is, cBaum& baum) {
            if (is >> baum.art && baum.art != "-")
                return is >> baum.hoch >> baum.posi;
            else
                return is;
        }
};


int main()
{
    std::vector<cBaum> wald;

    do {
        std::cout << "Bitte (Art, Hőhe, G. Länge, G. Breite) angeben: ";

        cBaum baum;
        if (std::cin >> baum)
        {
            if (!baum.valid()) // "-" entered
                break;
            wald.push_back(baum);
        } else
        {
            if (std::cin.eof())
                break;
            std::cout << "Ungűltiger Eintrag\n";
            std::cin.clear();
            std::cin.ignore(1024, '\n');
        }
    } while (true);

    for (auto& baum : wald)
        std::cout << baum << std::endl;
}
