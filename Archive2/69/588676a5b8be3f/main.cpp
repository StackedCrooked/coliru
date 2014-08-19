#include <iostream>
 
// 2d box
class Box2d {
public:
    float m_MaxX;
    float m_MaxY;
    float m_MinX;
    float m_MinY;
 
    Box2d(float minX, float maxX, float minY, float maxY)
    {
        m_MaxX = maxX;
        m_MaxY = maxY;
        m_MinX = minX;
        m_MinY = minY;
    }
 
    bool overlap(float minX, float maxX, float minY, float maxY)
    {
        if (minX >= m_MaxX) { return false; }
        if (m_MinX >= maxX) { return false; }
        if (minY >= m_MaxY) { return false; }
        if (m_MinY >= maxY) { return false; }
        return true;
    }
};
 
int main()
{
    Box2d b1(1, 2, 1, 2);
    Box2d b2(2, 3, 2, 3);
    Box2d b3(0, 1, 0, 1);
    Box2d b4(-2, 1, 0, 1);
 
    std::cout << std::boolalpha;
    std::cout << b1.overlap(b2.m_MinX, b2.m_MaxX, b2.m_MinY, b2.m_MaxX) << std::endl; // b1 overlaps b2? -> false
    std::cout << b2.overlap(b3.m_MinX, b3.m_MaxX, b3.m_MinY, b3.m_MaxX) << std::endl; // b2 overlaps b3? -> false
    std::cout << b3.overlap(b4.m_MinX, b4.m_MaxX, b4.m_MinY, b4.m_MaxX) << std::endl; // b3 overlaps b4? -> true
    std::cout << b4.overlap(b3.m_MinX, b3.m_MaxX, b3.m_MinY, b3.m_MaxX) << std::endl; // b4 overlaps b3? -> true
    
    return 0;
}