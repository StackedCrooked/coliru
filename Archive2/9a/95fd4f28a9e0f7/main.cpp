struct Vector2;

struct Matrix33
{
    float a00; float a01; float a02;
    float a10; float a11; float a12;
    float a20; float a21; float a22;

    Matrix33()
    {
        a00 = a01 = a02 = a10 = a11 = a12 = a20 = a21 = a22 = 0;
    }
    void AddValues(int line, float c1, float c2, float c3)
    {
        if (line == 0)
        {
            a00 = c1;
            a01 = c2;
            a02 = c3;
        }
        else if (line == 1)
        {
            a10 = c1;
            a11 = c2;
            a12 = c3;
        }
        else if (line == 2)
        {
            a20 = c1;
            a21 = c2;
            a20 = c3;
        }
    }

    static Matrix33 GetIdentity()
    {
        Matrix33 m;
        m.a00 = m.a11 = m.a22 = 1;

        return m;
    }

    Matrix33 operator*(const Matrix33 m)
    {
        Matrix33 result;
        result.AddValues(0, (a00*m.a00 + a01*m.a10 + a02*m.a20), (a00*m.a01 + a01*m.a11 + a02*m.a21), (a00*m.a02 + a01*m.a12 + a02*m.a22));
        result.AddValues(1, (a10*m.a00 + a11*m.a10 + a12*m.a20), (a10*m.a01 + a11*m.a11 + a12*m.a21), (a10*m.a02 + a11*m.a12 + a12*m.a22));
        result.AddValues(2, (a20*m.a00 + a21*m.a10 + a22*m.a20), (a20*m.a01 + a21*m.a11 + a22*m.a21), (a20*m.a02 + a21*m.a12 + a22*m.a22));

        return result;
    }
    Vector2 operator*(const Vector2 p);

};

struct Vector2
{
    float x;
    float y;
    float h;

    Vector2()
    {
        x = y = h = 0;
    }
    Vector2(float valueX, float valueY, float valueH)
    {
        x = valueX;
        y = valueY;
        h = valueH;

    }
    Vector2(float valueX, float valueY)
    {
        x = valueX;
        y = valueY;
        h = 1;
    }


    Vector2 Translate(Vector2 dir)
    {
        Matrix33 matrix = Matrix33::GetIdentity();

        matrix.a02 = dir.x;
        matrix.a12 = dir.y;

        return matrix * Vector2(x, y, h);
    }

    static Vector2 VectorOne()
    {
        return Vector2(1, 1, 1);
    }
    static Vector2 VectorUP()
    {
        return Vector2(0, 1, 0);
    }
    static Vector2 VectorFoward()
    {
        return Vector2(0, 0, 1);
    }
    static Vector2 VectorRight()
    {
        return Vector2(1, 0, 0);
    }

    Vector2 operator*(const int value)
    {
        return Vector2(x*value, y*value, h);
    }
    Vector2 operator/(const int value)
    {
        return Vector2(x / value, y / value, 1);
    }
    Vector2 operator+(const Vector2 value)
    {
        return  Vector2(x + value.x, y + value.y);
    }
    Vector2 operator-(const Vector2 value)
    {
        return  Vector2(x - value.x, y - value.y);
    }

};

    Vector2 Matrix33::operator*(const Vector2 p)
    {
        Vector2 result;

        result.x = a00*p.x + a01*p.y + a02*p.h;
        result.y = a10*p.x + a11*p.y + a12*p.h;
        result.h = a20*p.x + a21*p.y + a22*p.h;

        return result;
    }