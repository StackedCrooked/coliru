#include <boost/optional.hpp>

template<typename tag, typename value_type>
class id
{
    public:

		explicit id() = default;
		explicit id(value_type&& val) : m_id{val} { }

		friend bool operator==(const id& lhs, const id& rhs)
		{
			return lhs.m_id == rhs.m_id;
		}

		friend bool operator!=(const id& lhs, const id& rhs)
		{
			return lhs.m_id != rhs.m_id;
		}

		explicit operator value_type() const
		{ return m_id; }

		value_type val() const
		{ return m_id; }

		void setVal(value_type&& val)
		{ m_id = val; }

	private:
		value_type m_id{};
};

template<typename tag, typename impl>
using optional_tagged_id = id<tag, boost::optional<impl>>;

template<typename tag>
using optional_tagged_int32_id = optional_tagged_id<tag, int32_t>;

template<typename tag>
using id_type = optional_tagged_int32_id<tag>;

template<typename T, typename tag = T>
class id_mixin : public T
{
	public:
		using id_type = optional_tagged_int32_id<tag>;

		template <typename... Args>
		explicit id_mixin(id_type id,
						  Args&&... args):
			T{std::forward<Args>(args)...},
			m_id{id}
		{

		}

		id_type id() const
		{
			return m_id;
		}

		void setId(id_type id)
		{
			m_id = id;
		}

	private:
		id_type m_id;
};




/// What I want to do : 
class Base
{ 
    public:
        Base() = default;
};
using IdentifiedBase = id_mixin<Base>;


class Derived : public Base
{ };


int main()
{    
	std::vector<IdentifiedBase*> v;
	v.push_back(new id_mixin<Derived>(id_mixin<Derived>::id_type{}));	
}
