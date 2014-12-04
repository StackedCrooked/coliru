#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct samplet;

template <typename T> istream& operator>>(istream& is, samplet<T>& s)
{
    char colon, open, close;

    int vec_size;

    if(is >> open && open == '<') {
        if(is >> vec_size >> colon && (colon == ':')) {
            vector<T> vec(vec_size);

            for(int i = 0; i < vec_size; ++i) {
                T value;
                if(is >> value) {
                    vec[i] = value;
                }
            }
            if(is >> close && close == '>') {
                s.set_data(vec);
                return is;
            }
        }
    } else {
        is.setstate(ios::badbit);
    }
    return is;
}

int main()
{

    
}
