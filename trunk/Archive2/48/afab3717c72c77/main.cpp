

#include <iostream>
#include <typeinfo>
#include <map>

#include <typeindex>

class Base {
public:

    virtual int getCompType() = 0;
    
    template<typename T>
    static int getCompTypeImpl()
    {
        return getNextCompType<T>();
    }

protected:

	template<typename T>
	static int getNextCompType()
	{
		auto iter = m_table.find(std::type_index(typeid(T)));
		if (iter != m_table.end())
		{
			return iter->second;
		}
		else
		{
			m_table.insert(std::make_pair(std::type_index(typeid(T)), ++nextType));
			return nextType;
		}
	}

private:
	static std::map<std::type_index, int> m_table;
    static int nextType;
};

std::map<std::type_index, int> Base::m_table;
int Base::nextType = 0;

class Real1 : public Base {
public:

	int getCompType() override
	{
		return Base::getNextCompType<Real1>();
	}
};

class Real2 : public Base {
public:

	int getCompType() override
	{
		return Base::getNextCompType<Real2>();
	}
};



template<typename T>
int getCompType()
{
    return T:: template getCompTypeImpl<T>();
}


int main()
{
    Real1 v1;
	Real2 v2;
    Real2 v3;

    std::cout << v1.getCompType() << std::endl;
	std::cout << v2.getCompType() << std::endl;
    std::cout << v3.getCompType() << std::endl;
    
    
    std::cout << getCompType<Real1>() << std::endl;
    std::cout << getCompType<Real2>() << std::endl;

}