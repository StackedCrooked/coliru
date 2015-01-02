#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

namespace VenkataLibrary {

template <class T>
class DoubleArray {
private:
    T* m_pArray;

    unsigned int m_uiBase; // base to note is array index starts from 0 or 1.
    unsigned int m_rows;
    unsigned int m_columns;

    class Row {
        unsigned int m_uiRow;
        DoubleArray& m_dblArray;
    public:
        Row(unsigned int rowNo, DoubleArray& dblArray) : m_uiRow(rowNo), m_dblArray(dblArray) { }

        T& operator[](const int column) {
            return m_dblArray.select(m_uiRow, column);
        }
    };

public: 

    DoubleArray(unsigned int rows, unsigned int columns) : m_rows(rows), m_columns(columns) {
        m_pArray = new T(m_rows * m_columns);
         memset((void*)m_pArray, 0x00, sizeof(T) * (m_rows-1) * (m_columns-1)); //**// I am initializing memory to zero**
    }

    Row operator[] (unsigned int uiRow) {
        return Row(uiRow, *this);
    }

    T& select(unsigned int uiRow, unsigned int uiCol) {
        return m_pArray[uiRow * m_columns + uiCol];
    }
};

};

void main() {

    Array<unsigned int> myIntArray(10, 0);
    DoubleArray<unsigned int> myDblArray(10, 10);

    cout << myDblArray[1][1] << std::endl; //**// System crashes here. And I am expecting zero** here.

    myIntArray[0] = 2;

     cout << myIntArray[0] << std::endl;
}