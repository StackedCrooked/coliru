//             Copyright Evgeny Panasyuk 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/value_at_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/pair.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/phoenix/fusion.hpp>
#include <boost/phoenix.hpp>

#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>

#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <string>

using namespace boost;
using namespace std;

using fusion::at_key;
using fusion::at_c;

// ____________________________________________________________________________________ //
namespace implementation
{

namespace res_of=boost::fusion::result_of;
using namespace boost::fusion;
using mpl::_;

template<typename In,typename First,typename Last,typename HitEnd>
struct assoc_seq_to_mpl_vector_iteration;
template<typename In,typename First,typename Last>
struct assoc_seq_to_mpl_vector_iteration<In,First,Last,mpl::false_>
{
    typedef typename res_of::next<First>::type Next;
    typedef typename res_of::equal_to<Next,Last>::type HitEnd;
    typedef typename mpl::apply
    <
        typename In::operation,
        typename assoc_seq_to_mpl_vector_iteration
        <
            In, Next, Last, HitEnd
        >::type,
        fusion::pair
        <
            typename res_of::key_of<First>::type,
            typename res_of::value_of_data<First>::type
        >
    >::type type;
};
template<typename In,typename First,typename Last>
struct assoc_seq_to_mpl_vector_iteration<In,First,Last,mpl::true_>
{
    typedef typename In::state type;
};
template<typename FusionAssociativeSequence>
struct assoc_seq_to_mpl_vector
{
    typedef typename res_of::begin<FusionAssociativeSequence>::type First;
    typedef typename res_of::end<FusionAssociativeSequence>::type Last;
    typedef typename res_of::equal_to<First,Last>::type HitEnd;
    typedef typename assoc_seq_to_mpl_vector_iteration
    <
        mpl::front_inserter< mpl::vector<> >, First, Last, HitEnd
    >::type type;
};

template<typename FusionAssociativeSequence,typename ValueTypeTransform>
struct fusion_assoc_transform
{
    typedef typename res_of::as_map
    <
        typename mpl::transform
        <
            typename assoc_seq_to_mpl_vector<FusionAssociativeSequence>::type,
            fusion::pair
            <
                res_of::first<_>,
                mpl::apply_wrap1
                <
                    typename mpl::lambda<ValueTypeTransform>::type,
                    res_of::second<_>
                >
            >
        >::type
    >::type type;
};

struct get_fusion_pair_value
{
   template <typename Sig> struct result;
   template <typename FusionPair>
   struct result<const get_fusion_pair_value(FusionPair&)>
   {
      typedef typename res_of::second<FusionPair>::type &type;
   };
   template <typename FusionPair>
   struct result<const get_fusion_pair_value(const FusionPair&)>
   {
      typedef const typename res_of::second<FusionPair>::type &type;
   };
   template<typename FusionPair>
   typename result<const get_fusion_pair_value(FusionPair&) >::type
   operator()(FusionPair &fp) const
   {
      return fp.second;
   }
   template<typename FusionPair>
   typename result<const get_fusion_pair_value(const FusionPair&) >::type
   operator()(const FusionPair &fp) const
   {
      return fp.second;
   }
};

BOOST_PHOENIX_ADAPT_CALLABLE(fp_second, get_fusion_pair_value, 1)

/*struct push_back_record_to_vector
{
    template<typename Pair>
    void operator()(const Pair &pair) const
    {
        at_c<0>(pair).second.push_back(at_c<1>(pair).second);
    }
};*/

template<bool original_data_is_not_const> struct conditional_const_cast;
template<> struct conditional_const_cast<true>
{
    template<typename T> T& operator()(const T &t)
    {
        return const_cast<T&>(t);
    }
};
template<> struct conditional_const_cast<false>
{
    template<typename T> const T& operator()(const T &t)
    {
        return t;
    }
};

template<bool original_data_is_not_const>
struct indexed_reference
{
    unsigned index;
    indexed_reference(unsigned index_) : index(index_) {}

    template<typename Sig> struct result;
    template<typename VecNRec>
    struct result< indexed_reference(const VecNRec&) >
    {
        typedef typename VecNRec::second_type Container;
        typedef typename mpl::if_c
        <
            original_data_is_not_const,
            typename Container::reference,
            typename Container::const_reference
        >::type type;
    };
    template<typename VecNRec>
    typename result< indexed_reference(const VecNRec&) >::type
    operator()(const VecNRec &vec_n_rec) const
    {
        // Original data is not const, so const_cast will not result in UB.
        // This is required for efficient initialization of struct of references
        return conditional_const_cast<original_data_is_not_const>()(vec_n_rec.second[index]);
    }
};

template<typename FusionSequence>
class scattered_vector
{
    typedef typename fusion_assoc_transform< FusionSequence, std::vector<_> >::type vectors_type;
    vectors_type vectors;
public:
    typedef FusionSequence record;
    typedef typename fusion_assoc_transform< FusionSequence, boost::add_reference<_> >::type references_record;
    typedef typename fusion_assoc_transform
    <
        FusionSequence,
        boost::add_reference< boost::add_const<_> >
    >::type const_references_record;

    unsigned size() const
    {
        return unsigned(fusion::deref_data(fusion::begin(vectors)).size());
    }
    void push_back(const record &rec)
    {
        typedef fusion::vector<vectors_type&,const record&> zip_type;
        using phoenix::arg_names::arg1; using phoenix::at_c; using phoenix::push_back;
        fusion::for_each
        (
            fusion::zip_view<zip_type>( zip_type(vectors,rec) ),
            push_back( fp_second(at_c<0>(arg1)), fp_second(at_c<1>(arg1)) )//push_back_record_to_vector()
        );
    }
    references_record operator[](unsigned index)
    {
        return references_record( fusion::transform(vectors,indexed_reference<true>(index)) );
    }
    const_references_record operator[](unsigned index) const
    {
        return const_references_record( fusion::transform(vectors,indexed_reference<false>(index)) );
    }
    template<typename MemberTag> typename res_of::value_at_key< vectors_type, MemberTag >::type::reference
    part_at(unsigned index)
    {
        return at_key<MemberTag>(vectors)[index];
    }
    template<typename MemberTag> boost::iterator_range<typename range_iterator
    <
        typename res_of::value_at_key< vectors_type, MemberTag >::type>::type
    >
    part_range()
    {
        return boost::iterator_range<typename range_iterator
        <
            typename res_of::value_at_key< vectors_type, MemberTag >::type>::type
        >( at_key<MemberTag>(vectors) );
    }
};

} // end of namespace implementation

// ____________________________________________________________________________________ //

struct test_case
{
    test_case(const string &str)
    {
        cout << str << ":" << endl;
    }
    ~test_case()
    {
        cout << string(16,'_') << endl;
    }
};

#ifdef _MSC_VER
    __declspec(noinline) void asm_marker(int line) { volatile int i=line; };
    #define ASM_MARKER asm_marker(__LINE__)
#else
    #define ASM_MARKER
#endif

// ____________________________________________________________________________________ //

// Defenition of structure:

namespace ScatteredRecordTags
{
    struct name;
    struct age;
}

typedef fusion::map
<
    fusion::pair< ScatteredRecordTags::name, string >,
    fusion::pair< ScatteredRecordTags::age, int >
> ExampleRecord;

// ____________________________________________________________________________________ //

int main()
{
    namespace var=ScatteredRecordTags;
    typedef implementation::scattered_vector<ExampleRecord> Vector;
    typedef Vector::record Record;

    // Get types as:
    //   fusion::result_of::value_at_key<Record,var::name>::type
    //   fusion::result_of::value_at_key<Record,var::age>::type

    Vector vec;
    vec.size();
    {
        test_case t("Filling...");
        vec.push_back( Record(string("One"),1) );
        vec.push_back( Record(string("Two"),2) );
        vec.push_back( Record(string("Three"),3) );
        cout << "size=" << vec.size() << endl;
    }
    {
        test_case t("Access by const zipped structs");
        const Vector &const_vec=vec;
        for(unsigned i=0,size=const_vec.size();i!=size;++i)
        {
            Vector::const_references_record r=const_vec[i];
            cout << at_key<var::name>(r) << " " << at_key<var::age>(r) << endl;
        }
    }
    {
        test_case t("Modify by zipped structs");
        ASM_MARKER;
        for(unsigned i=0,size=vec.size();i!=size;++i)
        {
            ASM_MARKER;
            Vector::references_record r=vec[i];
            ASM_MARKER;
            at_key<var::name>(r)+="_postfix";
            at_key<var::age>(r)+=10;
            ASM_MARKER;
        }
    }
    {
        test_case t("Per part element access");
        for(unsigned i=0,size=vec.size();i!=size;++i)
            cout << vec.part_at<var::name>(i) << " " << vec.part_at<var::age>(i) << endl;
    }
    {
        test_case t("Per part range access");
        copy(vec.part_range<var::name>(),ostream_iterator<string>(cout,"\n"));
        copy(vec.part_range<var::age>(),ostream_iterator<int>(cout,"\n"));
    }
    {
        test_case t("Per part range accumulate");
        cout << "Age total=" << accumulate(vec.part_range<var::age>(),0) << endl;
    }
}

namespace size_test
{
    struct hand_made
    {
        string name;
        int age;
    };
    typedef ExampleRecord generated;

    BOOST_STATIC_ASSERT(sizeof(hand_made)==sizeof(generated));
}
