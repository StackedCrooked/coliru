#include <iostream>

#include <list>

/**
 * Pointers store.
 */
class PtrStore
{
    public:
		/**
		 * Destructor. Objects which were added to the store are deleted in the reverse
		 * order in which they were added.
		 */
		virtual ~PtrStore();

		/**
		 * Add object.
		 * @param obj pointer to the object. Object must contain virtual destructor,
		 * otherwise its deletion won't be handled by this class.
		 * @return @a obj as passed to the operator.
		 */
		template <typename T>
		T * operator()(T * obj);

		/**
		 * Delete object. Deletes an object and removes it from the store.
		 * @param obj object.
		 * @return 0 on success, obj on failure.
		 *
		 * @note this class isn't good at removing single elements. Operation requires
		 * iteration over list of objects (linear time O(N)).
		 */
		template <typename T>
		T * del(T * obj);

		/**
		 * Delete all. Performs deletion of all elements in the reverse order in which
		 * they were added.
		 * @return number of deleted objects.
		 */
		std::size_t delAll();

		/**
		 * Get size.
		 * @return number of objects in store.
		 */
		std::size_t size() const;

	private:
		bool del(void * obj);

		class AbstractPtrHolder
		{
			public:
				virtual ~AbstractPtrHolder();

				virtual void * ptr() const = 0;
		};

		template <typename T>
		class PtrHolder : public AbstractPtrHolder
		{
			public:
				PtrHolder(T * ptr);

				virtual ~PtrHolder();

				virtual void * ptr() const;

			private:
				T * m_ptr;
		};

	private:
		typedef std::list<AbstractPtrHolder *> PtrHoldersContainer;

	private:
		PtrHoldersContainer m_holders;
};


inline
PtrStore::~PtrStore()
{
	for (PtrHoldersContainer::reverse_iterator holder = m_holders.rbegin(); holder != m_holders.rend(); ++holder)
		delete *holder;
}

template <typename T>
inline
T * PtrStore::operator()(T * obj)
{
	m_holders.push_back(new PtrHolder<T>(obj));
	return obj;
}

template <typename T>
inline
T * PtrStore::del(T * obj)
{
	if (del(static_cast<void *>(obj)))
		return 0;
	else
		return obj;
}

inline
std::size_t PtrStore::delAll()
{
	std::size_t result = 0;
	while(!m_holders.empty()) {
		delete m_holders.back();
		m_holders.pop_back();
		result++;
	}
	return result;
}

inline
std::size_t PtrStore::size() const
{
	return m_holders.size();
}

inline
bool PtrStore::del(void * obj)
{
	for (PtrHoldersContainer::iterator holder = m_holders.begin(); holder != m_holders.end(); ++holder)
		if ((*holder)->ptr() == obj) {
			delete *holder;
			m_holders.erase(holder);
			return true;
		}
	return false;
}


inline
PtrStore::AbstractPtrHolder::~AbstractPtrHolder()
{
}

template <typename T>
PtrStore::PtrHolder<T>::PtrHolder(T * ptr):
	m_ptr(ptr)
{
}

template <typename T>
PtrStore::PtrHolder<T>::~PtrHolder()
{
	delete m_ptr;
}

template <typename T>
void * PtrStore::PtrHolder<T>::ptr() const
{
	return static_cast<void *>(m_ptr);
}

///////////////////////////////////////

class A
{
    public:
        ~A() 
        {
            std::cout << "A dtor" << "\n";
        }
};

class B
{
    public:
        B(int, int)
        {
        }
    
        ~B() 
        {
            std::cout << "B dtor" << "\n";
        }
};

class X
{
    public:
        X(): 
            m_a(m_store(new A)),
            m_b(m_store(new B(1, 2)))
        {
        }
    
    private:
        PtrStore m_store;
        A * m_a;
        B * m_b;
};

int main()
{
    X x;
    return 0;
}