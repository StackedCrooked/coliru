#include <iostream>
#include <functional>
#include <queue>
#include <future>
#include <type_traits>
#include <algorithm>
#include <ostream>
#include <sstream>      // std::ostringstream

class AbstractAction
{
    public:
        std::string getOwner() { return owner_; }
    
        void run() = 0;
        void sendTo(CommInterface* commInterface) = 0;
    
    private:
        Model* model_;
        std::string owner_;
};

class BuildingBuilder : public AbstractAction
{
    public:
        void run() override
        {
            model->buildBuilding(type_, position_);
        }
        
        void sendTo(CommInterface* commInterface) override
        {
            commInterface->sendBuildingBuilder(type_, position_);
        }
        
    private:
        Structure type_;
        sf::Vector2u position_;
};

class InfoGetter : public AbstractAction
{
    public:
        void run() override
        {
            result_ = model->getInfo(position_);
        }
    
        void sendTo(CommInterface* commInterface) override
        {
            commInterface->sendInfo(result_);
        }
        
    private:
        sf::Vector2u position_;
        std::string result_;
};

class Model
{
    public:
        void doAction()
        {
            AbstractAction* action = queue.pop();
            try
            {
                action->run();
                commInterface->sendNotification(action->getOwner(), "success");
                action->sendTo(commInterface);
            }
            catch(std::exception& e)
            {
                commInterface->sendNotification(action->getOwner(), e.what());
            }
        }
};

int main()
{
    Model model;
    model.addAction("Bob", Action::BuildingBuilder, Structure::Bar, (0, 0));
    
    model.doAction();
    
    return 0;
}