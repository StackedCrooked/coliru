#include <iostream>
#include <tuple>
#include <vector>
#include <type_traits>

template <typename... Ts>
struct pack {};

template <typename T, typename... Ts>
constexpr bool Contains = false;

template <typename T, typename U, typename... Ts>
constexpr bool Contains<T, U, Ts...> = Contains<T, Ts...>;

template <typename T, typename... Ts>
constexpr bool Contains<T, T, Ts...> = true;

template <bool...> 
constexpr bool All = true;

template <bool Head, bool... Tail>
constexpr bool All<Head, Tail...> = Head && All<Tail...>;

template <typename Subset, typename Set>
struct IsSubset;

template <typename... Ts, typename... Us>
struct IsSubset<pack<Ts...>, pack<Us...>>
    : std::integral_constant<bool, All<Contains<Ts, Us...>...>> {};

template <typename... Components>
struct Entity
{
    std::tuple<Components...> comps;
        
    Entity() = default;
    
    Entity(Components... cs)
        : comps(cs...)
    {
    }

    void update()
    {
        std::cout << "Updating " << __PRETTY_FUNCTION__ << std::endl;
    }
};

template <typename... EntityTypes>
struct EntityCollection
{
    std::tuple<std::vector<EntityTypes>...> entities;

    template <typename EntityType>
    void add(EntityType e)
    {
        auto& cont = std::get<std::vector<EntityType>>(entities);
        cont.push_back(e);
    }

    template <typename... Components, typename F>
    void for_each_containing(F f)
    {        
        using expander = int[];
        (void)expander{ 0, (void(
             apply<Components...>(std::get<std::vector<EntityTypes>>(entities), f)
        ), 0)... };
    }

    template <typename... Components, typename... Ts, typename F>
    auto apply(std::vector<Entity<Ts...>>& entities, F f)
        -> std::enable_if_t<IsSubset<pack<Components...>, pack<Ts...>>{}>
    {
        for (auto& v : entities)
        {
            f(v);
        }
    }   

    template <typename... Components, typename... Ts, typename F>
    auto apply(std::vector<Entity<Ts...>>&, F)
        -> std::enable_if_t<!IsSubset<pack<Components...>, pack<Ts...>>{}>
    {
    } 
};

int main()
{
    Entity<int, short> a;
    Entity<long, int> b;
    Entity<float, double> c;
    
    EntityCollection<Entity<int, short>,
                     Entity<long, int>,
                     Entity<float, double>> collection;
    
    collection.add(a);
    collection.add(b);
    collection.add(c);
    
    collection.for_each_containing<int>([](auto& c){ c.update(); });
    std::cout << std::endl;
    
    collection.for_each_containing<float>([](auto& c){ c.update(); });
    std::cout << std::endl;
    
    collection.for_each_containing<short>([](auto& c){ c.update(); });
    std::cout << std::endl;
    
    collection.for_each_containing<short, int>([](auto& c){ c.update(); });
}
