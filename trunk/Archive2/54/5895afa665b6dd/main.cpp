#include <string>
#include <vector>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <iostream>

template <typename> struct MenuT;

using Menu = boost::make_recursive_variant < 
        boost::recursive_wrapper<MenuT<int>>,
        boost::recursive_wrapper<MenuT<std::string>>,
        boost::recursive_wrapper<MenuT<bool>>
    >::type;

template <typename T> struct MenuT {
    struct Option {
        std::string           name;
        T                     item;
        boost::optional<Menu> submenu;

        Option(std::string name, T t, boost::optional<Menu> submenu = boost::none)
            : name(name), item(t), submenu(submenu)
        { }

        T choose() const;
        void print(int n) const;
    };

  private:
    template <typename U> friend struct MenuT;
    friend struct visitors;

    std::vector<Option> options;
    //boost::optional<Menu&> parent; // TODO e.g. link_parents_visitor
    enum ChoosingType { Normal, Remove };

  public:
    enum SpecialPosition : size_t { END_OF_MENU = size_t(-1) };

    MenuT() = default;
    MenuT(std::initializer_list<Option> options) : options(options) {}

    void insert(const std::string &itemName, const T &t, boost::optional<Menu> submenu = boost::none, size_t pos = END_OF_MENU) {
        auto it = (pos == END_OF_MENU 
                ? options.end() 
                : std::next(options.begin(), std::min(pos, options.size())));

        options.emplace(it, itemName, t, submenu);
    }

    T choose() const { return chosenItem().first; }
    int print() const;

  private:
    std::pair<T, int> chosenItem(ChoosingType = Normal) const;
};

struct visitors {
    struct simple : boost::static_visitor<>
    {
        void operator()(Menu& m) const { boost::apply_visitor(*this, m); }

        template <typename T> void operator()(MenuT<T>& m) const {
            std::cout << "-----------\n";
            
            for (auto& o : m.options) {
                std::cout << "option '" << o.name << "':\t" << o.item << "\n";
                if (o.submenu)
                    (*this)(*o.submenu);
            }
        }
    };
}; 

static const visitors::simple demo { };

int main()
{
    Menu menu = MenuT<int> { 
        { "one",   1 },
        { "two",   2 },
        { "three", 3 },

        { "forty-two", 42, 
                Menu(MenuT<std::string> {
                    {"Life, The Universe And Everything", "LtUae"},
                    {"Dent", "Arthur", 
                        Menu(MenuT<bool> {
                            {"yes", true},
                            {"no", false},
                        })
                    },
                })
        },
    };

    std::cout << std::boolalpha;
    demo(menu);
}
