class Counter
{
public:
   static unsigned int m_cnt;
};

unsigned int Counter::m_cnt = 0 ;

class Rectangle
{
public:
   Rectangle();
private:
   int m_width;
   int m_height;
};

Rectangle::Rectangle()
{
   m_width = m_height = 25 ;
   // Counter::m_cnt++;  ***commented out
}


Rectangle rect1;
