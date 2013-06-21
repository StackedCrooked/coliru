    #include <type_traits>

    template <int m, int n>
    class matrix {
    public:

        template<typename T = matrix>
        typename std::enable_if<
            std::is_same<T, matrix<4,4>>::value>
            ::type
        translate(float x, float y, float z) {
            // Do stuff
        }

    private:
        float mat[m * n];
    };

    int main() {
        matrix<4, 3> mat3;
        mat3.translate(1.0f, 1.0f, 1.0f);
    }
