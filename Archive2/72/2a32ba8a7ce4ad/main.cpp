#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <boost/optional.hpp>

//shared mem
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/unordered_map.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/creation_tags.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>


#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>

#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/functional/hash.hpp>
#include <boost/variant/detail/hash_variant.hpp>


namespace bip=boost::interprocess;
namespace bmi=boost::multi_index;


struct SrValue
{
    uint64_t nVal1;
    uint64_t nVal2;
	uint64_t nVal3;

	SrValue():nVal1(0),nVal2(0),nVal3(0){};
	SrValue(uint64_t pi_nVal1,uint64_t pi_nVal2,uint64_t pi_nVal3):
		nVal1(pi_nVal1),nVal2(pi_nVal2),nVal3(pi_nVal3){};
};

class EmptyKey
{

};

//typedef bip::offset_ptr< bip::managed_shared_ptr<EmptyKey, bip::managed_shared_memory>::type> my_shared_ptr;
typedef bip::managed_shared_ptr<EmptyKey, bip::managed_shared_memory>::type my_shared_ptr;





template<typename T>
class CrUniqueKey
{



	struct f_visitor: public boost::static_visitor<void>
    {
    	f_visitor(bip::managed_shared_memory * pi_pSegmentManager):m_pSegmentManager(pi_pSegmentManager)
    	{
    	}

    	void operator()(uint64_t t) const {}
    
    
    	
    	void operator()(my_shared_ptr pi_DummyPointer) const 
    	{
    		  std::cout<<"here m_pSegmentManager "<<m_pSegmentManager<<" pi_DummyPointer " << pi_DummyPointer <<std::endl;
    		  if(m_pSegmentManager!=NULL && pi_DummyPointer)
    		  {
    			  std::cout<<"FreeDummyPointer"<<pi_DummyPointer<<std::endl;
    			  std::cout<<" counter use " << pi_DummyPointer.use_count()<<std::endl;
    			  //release pointer
    			  m_pSegmentManager->destroy_ptr(&pi_DummyPointer);
    			  
    		  }
    	}
    
    	bip::managed_shared_memory * m_pSegmentManager;
};

public:

	typedef boost::variant< my_shared_ptr ,T> impl_type;


  
  

  
  CrUniqueKey()
  {
	  
  }

  CrUniqueKey(const T& t):m_pSegmentManager(NULL),impl(t){}




  ~CrUniqueKey(){
	  if(empty())
	  {
		  std::cout <<"in destructor " << this <<std::endl;
		  boost::apply_visitor(f_visitor(m_pSegmentManager),impl);
	  }
  }

  bool empty()const{return impl.which()==0;}
  
  T& get(){return boost::get<T>(impl);}
  const T& get()const{return boost::get<T>(impl);}

  friend bool operator==(const CrUniqueKey& x,const CrUniqueKey& y){return x.impl==y.impl;}
  friend std::size_t hash_value(const CrUniqueKey& x){return boost::hash<impl_type>()(x.impl);}
  friend std::size_t hash_value(CrUniqueKey& x){return boost::hash<impl_type>()(x.impl);}


  void SetValue(T & val)
  {
	  impl = val;
  }

  void SetEmptyKey()
  {
	  if(m_pSegmentManager!=NULL)
		  impl = bip::make_managed_shared_ptr(m_pSegmentManager->construct< EmptyKey >(bip::anonymous_instance)(), *m_pSegmentManager);
	  else
		  std::cout<<"error"<<std::endl;
  }

  void SetSegmentManager(bip::managed_shared_memory * pi_pSegmentManager)
  {
	  m_pSegmentManager = pi_pSegmentManager;
  }

  //debug function
  friend std::ostream &operator<<(std::ostream &os, const CrUniqueKey & pi_uniqueKey)
  {
	  os <<"[" << (pi_uniqueKey.empty()?"empty":"") << "]="<< pi_uniqueKey.impl;
	  return os;
  }
  
private:
  
  bip::managed_shared_memory * m_pSegmentManager;
  impl_type impl;


};


struct UsersKey2
{
  boost::optional<uint64_t>  IMSI;
  boost::optional<uint32_t>  IMEI;
};

  

struct UsersKey
{
  CrUniqueKey<uint64_t>  IMSI;
  CrUniqueKey<uint32_t> IMEI;


  SrValue value;

  UsersKey(){}

  friend bool operator==(const UsersKey& a1, const UsersKey& a2)
  {
	  return a1.IMSI == a2.IMSI &&
		  a1.IMEI == a2.IMEI ;
  }

  friend std::ostream &operator<<(std::ostream &os, const UsersKey & usersKey)
  {
	  os << "this=" 	<<  &usersKey  <<std::endl;
	  os << "IMSI=" 	<<  usersKey.IMSI  <<std::endl;
	  os << "IMEI=" 	<<  usersKey.IMEI  <<std::endl;

	  return os;
  }


  UsersKey(UsersKey2 & pi_Key,SrValue & pi_value,bip::managed_shared_memory * pi_SegmentManager)
  {
	  IMSI.SetSegmentManager(pi_SegmentManager);
	  IMEI.SetSegmentManager(pi_SegmentManager);
	  
	  if(pi_Key.IMSI)
	  {
		  IMSI.SetValue(pi_Key.IMSI.get());
	  }
	  else
		  IMSI.SetEmptyKey();

	  if(pi_Key.IMEI)
	  {
		  IMEI.SetValue(pi_Key.IMEI.get());
	  }
	  else
		  IMEI.SetEmptyKey();

	  value = pi_value;
  }


};





struct IMSI_tag{};
struct IMEI_tag{};


typedef bmi::hashed_unique<bmi::tag<IMSI_tag>,
	bmi::member<UsersKey, CrUniqueKey<uint64_t>  , &UsersKey::IMSI>,boost::hash< CrUniqueKey<uint64_t> >, std::equal_to< CrUniqueKey<uint64_t> >
	> hashed_by_IMSI;
typedef bmi::hashed_unique<bmi::tag<IMEI_tag>,
	bmi::member<UsersKey, CrUniqueKey<uint32_t> , &UsersKey::IMEI>,boost::hash< CrUniqueKey<uint32_t> >, std::equal_to< CrUniqueKey<uint32_t> >
	> hashed_by_IMEI;

//index struc definition
struct UsersKey_hash_indices:
  bmi::indexed_by<
	//boost::multi_index::hashed_unique< boost::multi_index::identity<UsersKey> >,
		hashed_by_IMSI,
		hashed_by_IMEI>{};

typedef boost::multi_index::multi_index_container<
  UsersKey,
  UsersKey_hash_indices,
  bip::allocator<UsersKey,bip::managed_shared_memory::segment_manager>
> GlobalHash;




class CrMultiParameterMultiIndex
{


	bip::offset_ptr<GlobalHash> m_pGlobalHash; 
	bip::managed_shared_memory * m_pSegment; 
	


	//only used to pass argument to unary functions
	UsersKey2 m_ParameterKeys;
public:
	CrMultiParameterMultiIndex():m_pGlobalHash(NULL),m_pSegment(NULL){}


	

	//return true if succeeded to insert and false if failed
	uint32_t Insert(UsersKey2 & key,SrValue & val)
	{
		std::cout<<"In Insert"<<std::endl;
		
		UsersKey keyToInsert(key,val,m_pSegment);

		std::cout<<"set manager "<< m_pSegment <<std::endl;
		
		return (m_pGlobalHash->insert(keyToInsert).second?1:0);
	}
    
    
//typename boost::multi_index::multi_index_container::index::IndexType::iterator
	template <typename TagType,typename SearchingKey>
	typename GlobalHash::index<TagType>::type::iterator GetIteratorBy(SearchingKey & key)
	{
		return  m_pGlobalHash->get<TagType>().find(key) ;
	}


	template <typename TagType,typename SearchingKey>
	uint32_t FindBy(SearchingKey & key,UsersKey2 & po_userKey)
	{
		uint32_t hRes = 1;

		

		//search for entry by TagType
		typedef  typename GlobalHash::index<TagType>::type 	IndexType;
		typename IndexType::iterator it =  GetIteratorBy<TagType>(key);

		//entry found
		if( it != m_pGlobalHash->get<TagType>().end() )
		{
			//replace all shared pointers by empty keys
			//po_userKey.CopyNonEmptyFields(*it);
			//po_userKey = *it;
			if((*it).IMSI.empty() == false)
				po_userKey.IMSI = (*it).IMSI;
			if((*it).IMEI.empty() == false)
				po_userKey.IMEI = (*it).IMEI;

		}
		//entry not found
		else
			hRes = 0;

		
		return hRes;
	}

	template <typename TagType,typename SearchingKey>
	uint32_t RemoveBy(SearchingKey & key)
	{
		
		//search for entry by TagType
		typedef  typename GlobalHash::index<TagType>::type 	IndexType;
		IndexType & l_Index = m_pGlobalHash->get<TagType>();
		typename IndexType::iterator it =  GetIteratorBy<TagType>(key);

		//entry found
		if( it != m_pGlobalHash->get<TagType>().end() )
		{
			std::cout<<"it removed " << *it <<std::endl;
			l_Index.erase(it);
			return 1;
		}
		//entry not found
		return 0;
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

				boost::function<void(CrUniqueKey<ModifyKeyType>&)> f = boost::bind(&CrMultiParameterMultiIndex::ModifyKey<ModifyingTagType,CrUniqueKey<ModifyKeyType> >, this, _1);

				//modify key failed
				if(m_pGlobalHash->modify_key(itToModify , f)==false)
					hRes = 0;
			}
		}
		//entry not found
		else
			hRes = 0;
		return hRes;
	}
    
    uint32_t Init()
    {
    	uint32_t hRes = 1;
	

    
        bip::shared_memory_object::remove("gogo"); 
        m_pSegment  =  new  bip::managed_shared_memory( bip::create_only, "gogo"  , 999999999);  

	    	m_pSegment->find_or_construct<GlobalHash>("GlobalHash")(
                GlobalHash::ctor_args_list(),
                GlobalHash::allocator_type(m_pSegment->get_segment_manager()));
    
        m_pGlobalHash = m_pSegment->find<GlobalHash>("GlobalHash").first;

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
template <> inline void CrMultiParameterMultiIndex::ModifyKey<IMSI_tag>(CrUniqueKey<uint64_t> & po_Key){po_Key = m_ParameterKeys.IMSI.get();}
template <> inline void CrMultiParameterMultiIndex::ModifyKey<IMEI_tag>(CrUniqueKey<uint32_t> & po_Key){po_Key = m_ParameterKeys.IMEI.get();}

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
    
    SrValue multival(5,6,7);
	UsersKey2 key;
	key.IMSI = 0;
	
    std::cout<<"before inserted"<<std::endl;
    m_multiParam.Insert( key , multival);
	uint64_t nImsi = 0;
	if(m_multiParam.RemoveBy<IMSI_tag>( nImsi ))
		std::cout<<"removed"<<std::endl;

	return 1;
}