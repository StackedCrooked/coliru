template<class T>
struct vec4
{
    T x, y, z, w;

    vec4() :x(0), y(0), z(0), w(0) {}
    vec4(T x, T y, T z, T w) :x(x), y(y), z(z), w(w) {}
    vec4(const vec4& v) :x(v.x), y(v.y), z(v.z), w(v.w) {}
};


template<class T>
struct mat4
{
    union
    {
        T elements[16];
        vec4<T> columns[4];
    };

    mat4()
    {
        for (int i = 0; i < 4 * 4; i++)
        {
            elements[i] = 0;
        }
    }
};

template struct mat4<double>;

int main() {}