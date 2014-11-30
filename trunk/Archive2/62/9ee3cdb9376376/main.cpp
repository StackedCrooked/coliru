#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <vector>
#include <boost/type_traits.hpp>
#include <boost/utility/result_of.hpp>

template <class SrcT, class DstT>
struct CopyCVR
{
    typedef typename boost::remove_reference<SrcT>::type base_src;
	typedef typename boost::remove_cv<typename boost::remove_reference<DstT>::type>::type base_dst;
	typedef typename boost::mpl::if_< boost::is_volatile<base_src>, volatile base_dst, base_dst >::type v_dst;
	typedef typename boost::mpl::if_< boost::is_const<base_src>, const v_dst, v_dst >::type cv_dst;
	typedef typename boost::mpl::if_< boost::is_reference<SrcT>, cv_dst&, cv_dst >::type type;
};

template <class typeT>
class Element2
{
	typeT elem[2];
public:
	typedef typeT elemType;

	Element2() { elem[0] = elem[1] = 0; }
	typeT& operator[](size_t i) { return elem[i]; }
};

template <class elementT>
class List
{
	std::vector<elementT> m_List;
public:
	typedef elementT list_type;
	typedef elementT& result_type;

	List() {};
	result_type operator[](size_t i) { return m_List[i]; }
	void Add(const elementT& el) { this->m_List.push_back(el); }
};

template <class ResultT, class typeT>
inline ResultT select(typeT& elem, int32_t num)
{
	return elem[num];
}

template <class List>
struct SelectFunctor
{
	int32_t m_elem;
public:
	SelectFunctor(int32_t elem) : m_elem(elem) {}

	typedef typename List::list_type::elemType listElem_type;
	typedef typename CopyCVR<typename List::result_type, listElem_type>::type result_type;

	result_type operator()(typename List::result_type elem) const
	{
		return select<result_type>(elem, m_elem);
	}
};

int main()
{
	typedef List<Element2<double> > ListDouble;
	ListDouble list;
	SelectFunctor<ListDouble> sel(1);
	list.Add(Element2<double>());
	double val = sel(list[0]);
	
	typedef boost::result_of<SelectFunctor<ListDouble>(typename ListDouble::list_type) >::type result_type;
	BOOST_STATIC_ASSERT(boost::is_same<result_type, double&>::value);
}