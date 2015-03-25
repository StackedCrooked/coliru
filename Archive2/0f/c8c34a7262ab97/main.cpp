#include <iostream>
#include <fstream>
using namespace std;

class Cell {
private:
    bool readOnly;
	int value;
public:
	Cell(int value, bool readOnly) {
		this->value = value;
		this->readOnly = readOnly;
	}

	bool isReadOnly() {return readOnly;}
	int getValue() const {return value;}
	void setValue(int value) {if (!readOnly) this->value = value;}
//	ostream& operator << (ostream& out, const Cell &rhs);
};

ostream& operator << (ostream &out, const Cell &rhs) {
	out << " " << rhs.getValue() << " ";
	
	return out;
}

void getFilename(char* filename) {
	cout << "Enter source file: ";
	cin >> filename;
}

int main() {
	//char* filename;
	//getFilename(filename);
	
	//Board *board = new Board(filename);

	Cell cell(0, true);
	cout << cell << endl;
	//delete board;
	return 0;
}
