#include <boost/function.hpp>
#include <boost/bind.hpp>

//shared mem
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/creation_tags.hpp>

namespace bmi=boost::multi_index;


struct UsersKey
{
  uint64_t  IMSI;
  uint32_t IMEI;

  friend bool operator==(const UsersKey& a1, const UsersKey& a2)
  {
      return a1.IMSI == a2.IMSI &&
		  a1.IMEI == a2.IMEI ;
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




class CrMultiParameterMultiIndex
{


	GlobalHash *  m_pGlobalHash; 
	UsersKey m_ParameterKeys;

	
public:
	CrMultiParameterMultiIndex():m_pGlobalHash(NULL){}

	//return true if succeeded to insert and false if failed
	uint32_t Insert(UsersKey & key){
	
		return (m_pGlobalHash->insert(key).second?1:0);
	}
    
    
	template <typename TagType,typename SearchingKey>
	typename GlobalHash::index<TagType>::type::iterator GetIteratorBy(SearchingKey & key){
		return  m_pGlobalHash->get<TagType>().find(key) ;
	}


	//Set Parameter will overload one of m_ParameterKeys entry and be used by ModifyKeyBy
	template<typename TagType,typename ValueType>
	uint32_t SetParameterKeys(ValueType pi_nVal){ return 0; }



	template <typename ModifyingTagType,typename ModifyingType>
		void ModifyKey(ModifyingType & po_Key);


	
	template <typename SearchingTagType,typename ModifyingTagType,typename SearchingKey,typename ModifyKeyType>
	uint32_t ModifyKeyBy(SearchingKey & key,ModifyKeyType & pi_Modifykey)
    {
		uint32_t hRes = 1;
		
		

		//search for entry by TagType
		typedef  typename GlobalHash::index<SearchingTagType>::type 	IndexType;
		typename IndexType::iterator it =  GetIteratorBy<SearchingTagType>(key);
		
		//entry found
		if( it != m_pGlobalHash->get<SearchingTagType>().end() )
		{
			//Set parameter to modify
			hRes = SetParameterKeys<ModifyingTagType>(pi_Modifykey);
			
			if(hRes == 1)
			{
				//get iteraror to modify
				typedef  typename GlobalHash::index<ModifyingTagType>::type 	ModifyIndexType;
				typename ModifyIndexType::iterator itToModify =  m_pGlobalHash->get<ModifyingTagType>().iterator_to(*it);

				boost::function<void( ModifyKeyType &)> f = boost::bind(&CrMultiParameterMultiIndex::ModifyKey<ModifyingTagType, ModifyKeyType >, this, _1);

				//modify key failed
				if(m_pGlobalHash->get<ModifyingTagType>().modify_key(itToModify , f)==false)
					hRes = 0;
			}
		}
		//entry not found
		else
			hRes = 0;
		return hRes;
	}
    
    uint32_t Init(){
    	uint32_t hRes = 1;
		m_pGlobalHash = new GlobalHash();
    	return hRes;
    }
};




template <typename ModifyingTagType,typename ModifyingType>
void CrMultiParameterMultiIndex::ModifyKey(ModifyingType & po_Key)
{
	std::cout<<"Modifier undefined po_Key = "<< po_Key << std::endl;
}

/*
**********************   MODIFY Keys overloading function   **********************
*/ 
template <> inline void CrMultiParameterMultiIndex::ModifyKey<IMEI_tag>( uint32_t & po_Key){po_Key = m_ParameterKeys.IMEI;}
template <> inline void CrMultiParameterMultiIndex::ModifyKey<IMSI_tag>(uint64_t & po_Key){po_Key = m_ParameterKeys.IMSI;}


/*
**********************   SET PARAMETER Keys overloading function   **********************
*/ 
template <> inline uint32_t CrMultiParameterMultiIndex::SetParameterKeys<IMSI_tag>(uint64_t pi_nImsi){
	m_ParameterKeys.IMSI = pi_nImsi; 
	return 1;
}

template <> inline uint32_t CrMultiParameterMultiIndex::SetParameterKeys<IMEI_tag>(uint32_t pi_nImei){
	m_ParameterKeys.IMEI = pi_nImei; 
	return 1;
}

int main()
{
 
    CrMultiParameterMultiIndex m_multiParam;

	m_multiParam.Init();
    
    UsersKey key;
	key.IMSI = 0;
	m_multiParam.Insert( key );
	
	uint64_t nFromImsi = 1;
	uint64_t nToImsi = 1;
	if(m_multiParam.ModifyKeyBy<IMSI_tag,IMSI_tag>( nFromImsi,nToImsi))
	std::cout<<"modify 0 to 1"<<std::endl;

	uint32_t nFromImei = 0;
	uint32_t nToImei = 0;
	if(m_multiParam.ModifyKeyBy<IMEI_tag,IMEI_tag>( nFromImei,nToImei))
		std::cout<<"modify 0 to 1"<<std::endl;


	return 1;
}