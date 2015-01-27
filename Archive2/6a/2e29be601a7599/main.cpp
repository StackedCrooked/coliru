#include <iostream>
#include <functional>
#include <forward_list>
#include <memory> 
template<typename... Arguments>
    class delegate{

	public:

		void operator()(Arguments... args){

			for(auto& callback : callbacks){
				callback(args...);
			}
		}


		void operator+=(std::function<void(Arguments... args)> function){
	        auto before_end = callbacks.before_begin();
	        for (auto& _ : callbacks)
	            ++ before_end;

	        callbacks.insert_after(before_end, function); //TODO need to replace this and check performance.
		}

	/* //TODO

		void operator-=(std::function<void(Arguments... args)> function){
			callbacks.erase(function);
		}
	*/

	private:
	    std::forward_list<std::function<void(Arguments... args)> > callbacks;

	};	
    
    
int main()
{
    
    delegate<int> printer;
    
    printer += [](int number){
       std::cout<<"A printer "<< number<<std::endl;   
    };
    
    printer += [](){
        class sum_class{
            public:
            int sum(int number){ return ++number; }
        };
        
        std::shared_ptr<sum_class> sum_object(new sum_class());
        
        return [sum_object](int number){ 
            
            std::cout<<"B printer "<<sum_object->sum(number)<<std::endl;

        };

    }();
    
    
    printer(20);
    

}
