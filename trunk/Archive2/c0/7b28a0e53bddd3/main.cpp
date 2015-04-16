#include <boost/range/algorithm.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <string>

using namespace boost;
using namespace std;

using Color = int;

struct Text
{
    string Text;
};

struct Image
{
    string FilePath;
};

struct Rect
{
    Color FillColor;
};

struct Draw : static_visitor<void>
{
    void operator()(const Text &x) const
    {
        cout << "Text: " << x.Text << endl;
    }
    void operator()(const Image &x) const
    {
        cout << "image: " << x.FilePath << endl;
    }
    void operator()(const Rect &x) const
    {
        cout << "Rect: " << x.FillColor << endl;
    }
    
};

int main()
{
    vector<variant<Text, Image, Rect>> items = 
    {
        Text{"text"},
        Image{"path"},
        Rect{55}
    };
    Draw v;
    for_each(items,apply_visitor(v));
}