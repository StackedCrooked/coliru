#include <iostream>
#include <ostream>
#include <utility>
#include <memory>
#include <vector>
#include <string>

using namespace std;

using Color = int;

struct Text;
struct Image;
struct Rect;

struct Visitor
{
    virtual void operator()(const Text &x) const=0;
    virtual void operator()(const Image &x) const=0;
    virtual void operator()(const Rect &x) const=0;
};

struct IVisitable
{
    virtual void accept(Visitor&)=0;
    virtual ~IVisitable(){}
};
template<typename Derived>
struct Visitable : IVisitable
{
    void accept(Visitor &v) override
    {
        v(*static_cast<Derived*>(this));
    }
};

struct Text: Visitable<Text>
{
    string Text = "text";
};

struct Image: Visitable<Image>
{
    string FilePath = "path";
};

struct Rect: Visitable<Rect>
{
    Color FillColor = 11;
};

struct Draw: Visitor
{
    void operator()(const Text &x) const override
    {
        cout << "Text: " << x.Text << endl;
    }
    void operator()(const Image &x) const override
    {
        cout << "image: " << x.FilePath << endl;
    }
    void operator()(const Rect &x) const override
    {
        cout << "Rect: " << x.FillColor << endl;
    }
    
};

int main()
{
    vector<unique_ptr<IVisitable>> items;
    items.emplace_back(new Text);
    items.emplace_back(new Image);
    items.emplace_back(new Rect);
    Draw v;
    for(auto &&x: items)
        x->accept(v);
}