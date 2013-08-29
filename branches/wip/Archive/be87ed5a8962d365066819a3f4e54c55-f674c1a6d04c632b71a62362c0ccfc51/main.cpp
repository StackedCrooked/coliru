#include <iostream>

using namespace std;


class Coordinate
{
    private:
        int m_x;
        int m_y;

    public:
        
        Coordinate(int x, int y)
        {
            m_x = x;
            m_y = y;
        
            cout << m_x << endl;
        }

        int getX() { return m_x; }
        int getY() { return m_y; }
};


int main()
{
    Coordinate c(1, 1);
    cout << c.getX() << endl;

}