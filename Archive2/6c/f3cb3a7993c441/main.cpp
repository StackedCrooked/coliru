#include <iostream>
#include <functional>
#include <queue>

enum class Action
{
    A,
    B
};

class ActionQueuer {
    private:
		std::queue<std::function<void()>> actions_;
	public:
		template<typename callable, typename Instance, typename... args>
		void queueAction(callable&& action, Instance&& instance, args&&... actionArgs)
        {
            std::function<void()> newAction = std::bind(std::forward<callable>(action), std::forward<Instance>(instance), std::forward<args>(actionArgs)...);
            actions_.push(newAction);
        }
        
		void executeOneAction()
        {
             if(!actions_.empty())
             {
        		std::function<void()> actionToExecute = actions_.front();
        		actions_.pop();
        		actionToExecute();
        	}
        }
        
		ActionQueuer() =default;
		~ActionQueuer()= default;
};

class TestPrinter {
public:
	TestPrinter()= default;
	void actionA(const std::string str) {std::cout << str << std::endl;}
    void actionB(const std::string& str, const std::string& str2) { std::cout << str << " " << str2 << std::endl; }
};

class Model
{
    public:
    	template<typename... args>
    	void addAction(Action action, args&&... actionArgs)
        {
            switch (action)
            {
                /*case Action::A:
                    actionQueuer.queueAction(&TestPrinter::actionA, &testPrinter, std::forward<args>(actionArgs)...);*/
                case Action::B:
                    actionQueuer.queueAction(&TestPrinter::actionB, &testPrinter, std::forward<args>(actionArgs)...);
                default:
                    return;
            }
        }
        
        void doAction()
        {
            actionQueuer.executeOneAction();
        }
    
    private:
        ActionQueuer actionQueuer;
        TestPrinter testPrinter;
};
 
int main() {
	std::string str("Hello");
    std::string str2("Hello2");

    
    Model model;
    /*model.addAction(Action::A, str);
    model.doAction();*/
    model.addAction(Action::B, str, str2);
    model.doAction();
    
	return 0;
} 