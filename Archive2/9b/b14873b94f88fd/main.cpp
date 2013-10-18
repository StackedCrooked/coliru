#include <iostream>
#include <string>

using namespace std;

namespace // windows_cruft
{
    using HANDLE = unsigned;
    HANDLE STD_OUTPUT_HANDLE = 1;
    HANDLE GetStdHandle(HANDLE) {return 42;}

    struct COORD { int X,Y; };
    void SetConsoleCursorPosition(HANDLE, COORD){}
}

class Heading {
private:
    string company;
    string report;

    static string defaultCompany() { return "ABC Industries"; }
    static string defaultReport () { return "Report"; }

public:
    Heading(string const& c = defaultCompany(), string const& r = defaultReport()) 
        : company(c), report(r) { }

    void storeInfo(string const& c, string const& r)
    {
        company = c;
        report  = r;
    }

    string getCompany() const { return company.empty()? defaultCompany() : company; }
    string getReport()  const { return report.empty()?  defaultReport()  : report;  }
};

void storeInfo(Heading&);
void showInfo(HANDLE, Heading);
void placeCursor(HANDLE, Heading);

int main() {
    Heading company;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    storeInfo(company);
    showInfo(screen, company);
    cin.ignore();
    cin.get();
    return 0;
}

/*****storeInfo*****/
void storeInfo(Heading &item) {
    string company;
    string report;
    cout << "\nPlease enter the company name.\n";
    getline(cin, company);
    cout << "\nPlease enter the report name.\n";
    getline(cin, report);
    item.storeInfo(company, report);
}

/*****placeCursor*****/
void placeCursor(HANDLE screen, int row, int col) {
    COORD position;
    position.Y = row;
    position.X = col;
    SetConsoleCursorPosition(screen, position);
}

/*****showInfo*****/
void showInfo(HANDLE screen, Heading item) {
    //system("cls");
    placeCursor(screen, 6, 25);
    cout << "********************************" << endl;
    placeCursor(screen, 8, 32);
    cout << item.getCompany() << endl;
    placeCursor(screen, 11, 36);
    cout << item.getReport() << endl;
    placeCursor(screen, 13, 25);
    cout << "********************************" << endl;
}
