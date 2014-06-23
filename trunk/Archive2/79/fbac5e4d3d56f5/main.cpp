#include <iostream>
#include <vector>
using namespace std;

int main()
{
    struct Face {
        Face() {

        }
        Face(const Face &) {
            cout << "copy constructed" << endl;
        }
        Face(Face &&) {
            cout << "move constructed" << endl;
        }

        Face &operator=(Face &&) {
            cout << "move called" << endl;
            return *this;
        }
        Face &operator=(const Face &) {
            cout << "copy called" << endl;
            return *this;
        }
    };
    cout << "sizeof(Face) = " << sizeof(Face) << endl;
    std::vector<Face> faces;

    for (int i = 0; i < 2; ++i)
    {
        Face f;

        faces.push_back(f);
    }
    cout << &*faces.begin() << endl << &*faces.end() << endl;

    return 0;
}
