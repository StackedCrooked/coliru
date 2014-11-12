#include <typeinfo>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/intrinsic.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/adapted/adt.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

class Bar {
    int integer_value;
  public:
    Bar(int i_val):integer_value(i_val)         { }
    int get_integer_value() const               { return integer_value;  } 
    void set_integer_value(const int i_val)     { integer_value = i_val; } 
};

class Foo {
    Bar bar_value;
  public:
    Foo(int i_val):bar_value(i_val)         { }
    Bar get_bar_value() const               { return bar_value;  } 
    void set_bar_value(const Bar b_val)     { bar_value = b_val; } 
};


BOOST_FUSION_ADAPT_ADT(Bar, 
        (int,  int,  obj.get_integer_value(), obj.set_integer_value(val)))

BOOST_FUSION_ADAPT_ADT(Foo, 
        (Bar,  Bar,  obj.get_bar_value(), obj.set_bar_value(val)))
        

#define MY_ADT_MEMBER_NAME(CLASSNAME, IDX, MEMBERNAME)                                                                                   \
        namespace boost { namespace fusion { namespace extension {                                                                       \
            template <> struct struct_member_name<CLASSNAME, IDX> { typedef char const *type; static type call() { return #MEMBERNAME; } \
        }; } } }

MY_ADT_MEMBER_NAME(Bar, 0, integer_value)

MY_ADT_MEMBER_NAME(Foo, 0, bar_value)


namespace visitor {

    template <typename Flavour, typename T> struct VisitorApplication;

    namespace detail
    {
        template <typename V, typename Enable = void>
        struct is_vector : boost::mpl::false_ { };

        template <typename T>
        struct is_vector<std::vector<T>, void> : boost::mpl::true_ { };

        namespace iteration
        {
            // Iteration over a sequence
            template <typename FusionVisitorConcept, typename S, typename N>
                struct members_impl
                {
                    // Type of the current member
                    typedef typename boost::fusion::result_of::value_at<S, N>::type   current_t;
                    typedef typename boost::mpl::next<N>::type                        next_t;
                    typedef boost::fusion::extension::struct_member_name<S, N::value> name_t;

                    static inline void handle(FusionVisitorConcept& visitor, const S& s)
                    {
                        visitor.start_member(name_t::call());
                        VisitorApplication<FusionVisitorConcept, current_t>::handle(visitor, boost::fusion::at<N>(s));
                        visitor.finish_member(name_t::call());
                        members_impl<FusionVisitorConcept, S, next_t>::handle(visitor, s);
                    }

                    static inline void read_handle(FusionVisitorConcept& visitor, S& s)
                    {
                        visitor.start_member(name_t::call());
                        VisitorApplication<FusionVisitorConcept, current_t>::read_handle(visitor, boost::fusion::at<N>(s));
                        visitor.finish_member(name_t::call());
                        members_impl<FusionVisitorConcept, S, next_t>::read_handle(visitor, s);
                    }

                };

            // End condition of sequence iteration
            template <typename FusionVisitorConcept, typename S>
                struct members_impl<FusionVisitorConcept, S, typename boost::fusion::result_of::size<S>::type>
                {
                    static inline void handle(FusionVisitorConcept const&, const S&) { /*Nothing to do*/ }
                    static inline void read_handle(FusionVisitorConcept const&, S&) { /*Nothing to do*/ }
                };

            // Iterate over struct/sequence. Base template
            template <typename FusionVisitorConcept, typename S>
                struct Struct : members_impl<FusionVisitorConcept, S, boost::mpl::int_<0>> {};

    } // iteration

    template <typename FusionVisitorConcept, typename T>
        struct array_application
        {
            typedef array_application<FusionVisitorConcept, T> type;

            typedef typename T::value_type value_type;

            static inline void handle(FusionVisitorConcept& visitor, const T& t)
            {
                visitor.empty_array();
                for (auto& el : t)
                    VisitorApplication<FusionVisitorConcept, value_type>::handle(visitor, el);
            }

            static inline void read_handle(FusionVisitorConcept& visitor, T& t)
            {
                visitor.empty_array();
                for (auto& el : t)
                    VisitorApplication<FusionVisitorConcept, value_type>::read_handle(visitor, el);
            }

        };

    template <typename FusionVisitorConcept, typename T>
        struct struct_application
        {
            typedef struct_application<FusionVisitorConcept, T> type;

            static inline void handle(FusionVisitorConcept& visitor, const T& t)
            {
                visitor.empty_object();
                iteration::Struct<FusionVisitorConcept, T>::handle(visitor, t);
            }

            static inline void read_handle(FusionVisitorConcept& visitor, T& t)
            {
                iteration::Struct<FusionVisitorConcept, T>::read_handle(visitor, t);
            }

        };

    template <typename FusionVisitorConcept, typename T, typename Enable = void>
        struct value_application
        {
            typedef value_application<FusionVisitorConcept, T> type;

            static inline void handle(FusionVisitorConcept& visitor, const T& t) {
                visitor.value(t);
            }

            static inline void read_handle(FusionVisitorConcept& visitor, T& t) {
                visitor.value(t);
            }

        };

    template <typename FusionVisitorConcept, typename T>
        struct value_application<FusionVisitorConcept, boost::optional<T> >
        {
            typedef value_application<FusionVisitorConcept, boost::optional<T> > type;

            static inline void handle(FusionVisitorConcept& visitor, const boost::optional<T>& t) {
                if (t)
                    VisitorApplication<FusionVisitorConcept, T>::handle(visitor, *t);
                else
                    ; // perhaps some default action?
            }

            static inline void read_handle(FusionVisitorConcept& visitor, boost::optional<T>& t) {
                if (t)
                    VisitorApplication<FusionVisitorConcept, T>::read_handle(visitor, *t);
                else
                    ; // perhaps some default action?
            }

        };

    template <typename FusionVisitorConcept, typename T>
        struct select_application
        {
            typedef
                //typename boost::mpl::eval_if<boost::is_array<T>,                  boost::mpl::identity<array_application<FusionVisitorConcept, T>>,
                typename boost::mpl::eval_if<detail::is_vector<T>,                  boost::mpl::identity<array_application <FusionVisitorConcept, T>>,
                typename boost::mpl::eval_if<boost::fusion::traits::is_sequence<T>, boost::mpl::identity<struct_application<FusionVisitorConcept, T>>,
                boost::mpl::identity<value_application<FusionVisitorConcept, T>>
                > >::type type;
        };

    } // detail

    template <typename FusionVisitorConcept, typename T>
        struct VisitorApplication : public detail::select_application<FusionVisitorConcept, T>::type
    {
    };
}

template <typename FusionVisitorConcept, typename T>
void apply_fusion_visitor(FusionVisitorConcept& visitor, T const& o)
{
    visitor::VisitorApplication<FusionVisitorConcept, T>::handle(visitor, o);
}

template <typename FusionVisitorConcept, typename T>
void apply_read_fusion_visitor(FusionVisitorConcept& visitor, T & o)
{
    visitor::VisitorApplication<FusionVisitorConcept, T>::read_handle(visitor, o);
}


struct DisplayMemberVisitor {
    typedef std::string result_type;

    DisplayMemberVisitor() { ss << std::boolalpha; }

    std::string complete() { return ss.str(); }

    void start_member (const char* name) { 
        std::cerr << __FUNCTION__ << ":\t'" << name << "'" << "\n"; 
        ss << "<" << name << ">";
    }
    void finish_member(const char* name) { 
        std::cerr << __FUNCTION__ << ":\t'" << name << "'" << "\n"; 
        ss << "</" << name << ">";
    }

    template <typename T> void value(T const& value) {
        std::cerr << __FUNCTION__ << ":\t" << value << "\n";
        ss << value;
    }

    //template <typename T> void value(boost::optional<T>& value);
    void empty_object() { std::cerr << __FUNCTION__ << "\n"; }
    void empty_array()  { std::cerr << __FUNCTION__ << "\n"; }

  private:
    std::stringstream ss;
};

struct ReadMemberVisitor {
    typedef std::string result_type;

    ReadMemberVisitor(std::string ss_) { ss  = ss_; }

    void start_member (const char* name) { 
        std::string tag = "<" + std::string(name) + ">";
        ss = ss.substr(tag.length(),ss.length());                      
    }
    void finish_member(const char* name) { 
        std::string tag = "</" + std::string(name) + ">";
        ss = ss.substr(tag.length(),ss.length());                              
    }

    template <typename T> void value(T &value) {
        auto pos = ss.find('<');
        std::string value_string = ss.substr(0,pos);
        value = boost::lexical_cast<T>(value_string);
        ss = ss.substr(pos,ss.length());
    }

private:
    std::string ss;
};

int main()
{
    Bar b(35),bo(0);
    Foo f(78);

    DisplayMemberVisitor vis;
    apply_fusion_visitor(vis, b);
    std::cout << "\n" << vis.complete() << "\n";

    ReadMemberVisitor rv(vis.complete());
    apply_read_fusion_visitor(rv, bo);

    return 0;
}

