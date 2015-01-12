#include <iostream>
#include <tuple>
#include <vector>
#include <type_traits>
#include <cstddef>
#include <utility>
#include <string>

template <typename... Ts>
struct pack {};

template <typename T, typename... Ts>
struct Contains : std::false_type {};

template <typename T, typename U, typename... Ts>
struct Contains<T, U, Ts...> : Contains<T, Ts...> {};

template <typename T, typename... Ts>
struct Contains<T, T, Ts...> : std::true_type {};

template <bool...> 
constexpr bool All = true;

template <bool Head, bool... Tail>
constexpr bool All<Head, Tail...> = Head && All<Tail...>;

template <typename Subset, typename Set>
struct IsSubset;

template <typename... Ts, typename... Us>
struct IsSubset<pack<Ts...>, pack<Us...>> : std::integral_constant<bool, All<Contains<Ts, Us...>{}...>> {};

template <typename... Components>
struct Entity
{
    std::tuple<Components...> comps;
        
    Entity() = default;
    
    std::string name; // < for demo only
    
    Entity(std::string n, Components... cs)
        : comps(cs...)
        , name(n)
    {
    }

    // sample update functio
    void update()
    {
        std::cout << "Updating " << name << std::endl;
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
        (void)expander{ 0, (void(apply<Components...>(std::get<std::vector<EntityTypes>>(entities), f)), 0)... };
    }
        
    template <typename... Components, typename... Ts, typename F>
    auto apply(std::vector<Entity<Ts...>>& entities, F f)
        -> std::enable_if_t<IsSubset<pack<Components...>, pack<Ts...>>{}>
    {
        for (auto&& v : entities)
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
    Entity<int, short> a{ "int,short", 1, 2 };
    Entity<long, int> b{ "long,int", 3, 4 };
    Entity<float, double> c{ "float,double", 5, 6 };
    
    EntityCollection<Entity<int, short>, Entity<long, int>, Entity<float, double>> collection;
    
    collection.add(a);
    collection.add(b);
    collection.add(c);
    
    collection.for_each_containing<int>([](auto&& e){e.update();});
    std::cout << std::endl;
    
    collection.for_each_containing<float>([](auto&& e){e.update();});
    std::cout << std::endl;
    
    collection.for_each_containing<short>([](auto&& e){e.update();});
    std::cout << std::endl;
    
    collection.for_each_containing<short, int>([](auto&& e){e.update();});
}
