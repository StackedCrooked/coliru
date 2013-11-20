
#include <iostream>
#include <vector>
#include <memory>

class SomeList
{
    struct concept_y
    {
    	virtual void do_stuff() = 0;
        virtual ~concept_y() {}
	};
	
	template<typename C>
	class concrete_concept : public concept_y
	{
	    C value;
			
		public:
			concrete_concept(C a) : value(a) { std::cout << "constr" << std::endl; }
            virtual ~concrete_concept() {  std::cout << "destr" << std::endl;  }
            
			void do_stuff() { std::cout << value << std::endl; }
	};

	std::vector<std::unique_ptr<concept_y>> daList;
    
public:
	SomeList() : daList() {}
	
	void do_stuff()
	{
		for (auto& x : daList)
			x->do_stuff();
	}
	
	template<typename C>
	void add(C newobject)
	{
		daList.push_back(std::unique_ptr<concept_y>(new concrete_concept<C>(newobject)));
	}
};

int main()
{
	SomeList sl;
	sl.add("hi there");
	sl.add(4.0);
	sl.add(5);
	sl.add("what else?");
	sl.do_stuff();
}
