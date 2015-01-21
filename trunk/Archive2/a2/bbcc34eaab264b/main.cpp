#include <map>
#include <vector>
#include <boost/variant/variant.hpp>

template <typename T>
struct Deferred
{
    typedef T value_type;
};

template <typename T>
struct DeferredContainer
{
	typedef typename T::value_type value_type;
	typedef typename T::iterator iterator;
	typedef typename T::const_iterator const_iterator;
	typedef typename T::size_type size_type;
	typedef typename T::reference reference;
};

template <typename T>
class ArrayObject;

class MixedArrayObject;
class DictionaryObject;
class NullObject;

class Containable;

template <typename T>
using ArrayObjectPtr = Deferred<ArrayObject<T>>;

using DictionaryObjectPtr = Deferred<DictionaryObject>; // DeferredContainer<DictionaryObject>
using MixedArrayObjectPtr = Deferred<MixedArrayObject>; // DeferredContainer<MixedArrayObject>
using NullObjectPtr = Deferred<NullObject>;

typedef boost::variant <
	NullObjectPtr,
	MixedArrayObjectPtr,
	DictionaryObjectPtr
> ContainerPtr;

typedef boost::variant <
	NullObjectPtr,
	MixedArrayObjectPtr,
	DictionaryObjectPtr
> ContainableObject;

class Containable
{
public:
	inline void SetContainer(ContainerPtr obj) { _container = obj; }
	inline ContainerPtr GetContainer() const { return _container; }

private:
	ContainerPtr _container;
};

template <typename T>
class ArrayObject : public Containable
{
public:
	typedef std::vector<T> list_type;
	typedef typename list_type::value_type value_type;
	typedef typename list_type::iterator iterator;
	typedef typename list_type::const_iterator const_iterator;
	typedef typename list_type::size_type size_type;
	typedef typename list_type::reference reference;

private:
	list_type list;
};

class MixedArrayObject : public ArrayObject<ContainableObject>
{
};

template <typename NameT, typename ValueT>
class DictionaryObjectBase : public Containable
{
public:
	typedef std::map<NameT, ValueT> list_type;

	typedef typename list_type::value_type value_type;
	typedef typename list_type::iterator iterator;
	typedef typename list_type::const_iterator const_iterator;
	typedef typename list_type::size_type size_type;
	typedef typename list_type::reference reference;

private:
	list_type list;
};

class DictionaryObject : public DictionaryObjectBase<int, ContainableObject>
{
};

class NullObject : public Containable
{
};

int main()
{
	DictionaryObject dictionary;
	MixedArrayObject arr;
}
