#include "/Archive2/78/7b45acd2e10386/main.cpp" // runtime `get`, `get_variant_t`

#include <tuple>
#include <type_traits>
#include <functional>
#include <cstddef>

template<class Cont>
using iterator_reference_t = typename std::iterator_traits<typename Cont::iterator>::reference;

template<class Cont>
using const_iterator_reference_t = typename std::iterator_traits<typename Cont::const_iterator>::reference;

template<class T> T declval();

template<class... Ts> struct common_type;
template<class... Ts>
using common_type_t = typename common_type<Ts...>::type;

template<class T>
struct common_type<T>{ using type = T; };

template<class T, class U, class... Ts>
struct common_type<T, U, Ts...>
{
    using helper = decltype(true ? declval<T>() : declval<U>());
    using type = common_type_t<helper, Ts...>;
};
        
template<class It>
struct iter_pair{ It current, end; };

template<class It>
iter_pair<It> make_iter_pair(It curr, It end){ return {curr, end}; }

template<class ValueType = void, class... Ts>
struct cattainer
{
    static_assert(sizeof...(Ts) > 0, "A cattainer needs at least one underlying container");

    // `std::set<T>` has `T` as the `value_type`, but you will only ever get a `T const` out of it,
    // so we need to inspect the iterators...
    using underlying_value_type = common_type_t<iterator_reference_t<unqual_t<Ts>>...>;
    using underlying_const_value_type = common_type_t<const_iterator_reference_t<unqual_t<Ts>>...>;

    using value_type = typename std::conditional<
            std::is_void<ValueType>{},
            underlying_value_type,
            ValueType
        >::type;
        
    using const_value_type = typename std::conditional<
            std::is_void<ValueType>{},
            underlying_const_value_type,
            ValueType
        >::type;
        
    std::tuple<Ts...> _conts;
    
    std::size_t size_impl(int_<0>) const{ return std::get<0>(_conts).size(); }
    template<int I>
    std::size_t size_impl(int_<I>) const{ return std::get<I>(_conts).size() + size_impl(int_<I-1>{}); }
    
    std::size_t size() const{ return size_impl(int_<sizeof...(Ts)-1>{}); }

    template<class T, class Parent>
    struct iterator_base
    {        
        Parent& _parent;
        
        using iterators = std::tuple<iter_pair<typename unqual_t<Ts>::iterator>...>;
        using inner_iterators = get_variant_t<iterators>;
        
        boost::optional<inner_iterators> _iters;
        std::function<void()> _setter;
        
        iterator_base(Parent& parent, bool end)
            : _parent(parent)
        {
            if (end)
            {
                static constexpr int last = sizeof...(Ts)-1;
                auto& cont = std::get<last>(_parent._conts);
                auto its = make_iter_pair(cont.end(), cont.end());
                _iters = inner_iterators{ make_tagged<last>(std::move(its)) };
                _setter = nullptr;
            }
            else
            {
                set_setter(int_<0>{});
                do
                {
                    _setter();
                } while (_setter && boost::apply_visitor(check_empty{ *this }, *_iters));
            }                    
        }
        
        template<int I>
        void set_setter(int_<I>){ _setter = [this]{ set_state<I>(); }; }
        void set_setter(int_<sizeof...(Ts)>) { _setter = nullptr; }
        
        template<int I>
        void set_state()
        {
            auto& cont = std::get<I>(_parent._conts);
            auto its = make_iter_pair(cont.begin(), cont.end());
            _iters = inner_iterators{ make_tagged<I>(std::move(its)) };
            
            set_setter(int_<I+1>{});
        }
        
        T operator*() const{ return boost::apply_visitor(dereference{}, *_iters); }
        
        iterator_base& operator++()
        {
            boost::apply_visitor(checked_increment{ *this }, *_iters);
            return *this;
        }
        
        bool operator==(iterator_base const& other) const
        {
            return boost::apply_visitor(equals{}, *_iters, *other._iters);
        }
        
        bool operator!=(iterator_base const& other) const
        {
            return !(*this == other);
        }
        
        // vvv visitor stuff
        struct check_empty
        {
            iterator_base& _parent;
            
            using result_type = bool;
            
            template<class Iters>
            result_type operator()(Iters& iters) const
            {
                return iters.value.current == iters.value.end;
            }
        };
        
        struct checked_increment
        {
            iterator_base& _parent;
            
            using result_type = void;
            
            template<class Iters>
            result_type operator()(Iters& iters) const
            {
                ++iters.value.current;
                
                while (_parent._setter && boost::apply_visitor(check_empty{ _parent }, *_parent._iters))
                    _parent._setter();
            }
        };
        
        struct dereference : boost::static_visitor<T>
        {
            template<class Iters>
            T operator()(Iters& iters) const{ return *iters.value.current; }
        };
        
        struct equals
        {
            using result_type = bool;
                        
            template<class Left, class Right>
            result_type operator()(Left const&, Right const&) const{ return false; }
            
            template<class Iters>
            result_type operator()(Iters const& left, Iters const& right) const
            {
                return left.value.current == right.value.current;
                //return std::tie(left.value.current, left.value.end) == std::tie(right.value.current, right.value.end);
            }
        };
        // ^^^ visitor stuff
    };
    
    using iterator = iterator_base<value_type, cattainer>;
    using const_iterator = iterator_base<const_value_type, cattainer const>;
    
    iterator begin(){ return {*this, false}; }
    iterator end(){ return {*this, true}; }
    const_iterator begin() const{ return {*this, false}; }
    const_iterator end() const{ return {*this, true}; }
    const_iterator cbegin() const{ return begin(); }
    const_iterator cend() const{ return end(); }
};

template<class ValueType = void, class... Ts>
cattainer<ValueType, Ts...> cat(Ts&&... ts){ return {std::forward_as_tuple(std::forward<Ts>(ts)...)}; }

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>

int main()
{
    std::vector<int> v{1, 2, 3};
    std::list<int> l{4, 5, 6};
    std::deque<int> d{7, 8, 9};
    std::set<int> s{10, 11, 12};
    
    auto catted = cat(v, l, d, s);
    for(int i : catted)
        std::cout << i << " ";
}