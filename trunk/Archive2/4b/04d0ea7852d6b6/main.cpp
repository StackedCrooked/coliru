#include <cstdlib>

template<class ValueType>
class stAlignedContainer
{
public:
    stAlignedContainer()
		: m_data(0)
		, m_dataSize(0)
	{ };

	stAlignedContainer(const void* data, size_t dataSize)
	{
		m_data = static_cast<const unsigned char *>(data);	
		m_dataSize = dataSize;
	};

	inline const ValueType& operator[] (unsigned short n) const
	{
		return ((ValueType*)m_data)[n];
	};

protected:
	const unsigned char * m_data;
	size_t m_dataSize;
};
//-----------------------------------------------------------------------------
template< class ValueType >
class stUnalignedContainer : public stAlignedContainer<ValueType>
{
public:
    typedef stAlignedContainer<ValueType> parent_type;

	stUnalignedContainer()
	{ };

	stUnalignedContainer(const void* data, size_t dataSize) : parent_type(data, dataSize)
	{ };

	inline const ValueType& operator[] (unsigned short n) const
	{
		return *((const ValueType*) &parent_type::m_data[ n * parent_type::m_dataSize ]);
	};
};