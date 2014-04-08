
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>


namespace bmi=boost::multi_index;


struct UsersKey
{
  uint64_t  IMSI;
  uint32_t IMEI;

  friend bool operator==(const UsersKey& a1, const UsersKey& a2)
  {
      return a1.IMSI == a2.IMSI && a1.IMEI == a2.IMEI ;
  }
};


struct IMSI_tag{};
struct IMEI_tag{};


typedef bmi::ordered_unique<bmi::tag<IMSI_tag>,
    bmi::member<UsersKey, uint64_t  , &UsersKey::IMSI> > order_by_IMSI;
typedef bmi::ordered_unique<bmi::tag<IMEI_tag>,
    bmi::member<UsersKey, uint32_t , &UsersKey::IMEI> >order_by_IMEI;

//index struc definition
struct UsersKey_indices:
  bmi::indexed_by<
		order_by_IMSI,
		order_by_IMEI>{};

typedef boost::multi_index::multi_index_container<
  UsersKey,
  UsersKey_indices
> GlobalHash;



template <typename MultiIndexType>
class CrMultiParameterMultiIndex
{


	GlobalHash *  m_pGlobalHash; 
	UsersKey m_ParameterKeys;

	
public:
	CrMultiParameterMultiIndex():m_pGlobalHash(NULL) {
		m_pGlobalHash = new GlobalHash();
	}

	template <typename TagType,typename SearchingKey>
	typename MultiIndexType::template index<TagType>::type::iterator GetIteratorBy(SearchingKey & key){
		return  m_pGlobalHash->template get<TagType>().find(key) ;
	}
    
        template <typename TagType,typename SearchingKey>
	void RemoveBy(SearchingKey & key)
	{
		
		//search for entry by TagType
		typedef  typename MultiIndexType::template index<TagType>::type 	IndexType;
		IndexType & l_Index = m_pGlobalHash.template get<TagType>();
		typename IndexType::iterator it =  GetIteratorBy<TagType>(key);

		//entry found
		if( it != m_pGlobalHash.template get<TagType>().end() )
		{
			l_Index.erase(it);
			
		}
		//entry not found
		
	}
};



int main()
{
 
    CrMultiParameterMultiIndex<GlobalHash> m_multiParam;
    
    uint64_t nIMSI=0;
    m_multiParam.RemoveBy<IMSI_tag>(nIMSI);
    
    std::cout<<"gogo"<<std::endl;
    return 1;
}