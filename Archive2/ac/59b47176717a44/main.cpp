#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

int main() {
    try { cout << stoi("testing") << " " << stoi("12345678910") << " " << stoi("123456789") << endl; }
    catch (invalid_argument &ex) {}
    catch (out_of_range &ex) {}
    cout << stoi("123456789") << endl;
	return 0;
}