#include <boost/tti/has_template.hpp>

BOOST_TTI_HAS_TEMPLATE(Template1)
BOOST_TTI_HAS_TEMPLATE(Template2)
BOOST_TTI_HAS_TEMPLATE(Template3)

struct Top
{
  template <class X> struct Template1 { };
  template <typename A,typename B,typename C> class Template2 { };
  template <typename A,typename B,typename C,int D> class Template3 { };
};
  
int main()
{
    static_assert( has_template_Template1<Top>::value, ""); // true
    static_assert( has_template_Template2<Top>::value, ""); // true
    static_assert(!has_template_Template3<Top>::value, ""); // false, not all typename/class template parameters
}
