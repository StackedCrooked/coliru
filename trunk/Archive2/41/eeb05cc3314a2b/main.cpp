#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// For demo purposes
class CBaseAnimation
{
public:
    CBaseAnimation(std::string const& name) : m_name{name} {}
    bool NeedUpdate() const { return true; }
    bool GetPaused() const { return false; }
    void Update(float dt) {}
    std::string const& Name() const { return m_name; }
    
private:
    std::string m_name;
};

enum class PendingAction { Add, Remove };

class Operation
{
public:
    PendingAction action;
    std::shared_ptr<CBaseAnimation> animation;
};


std::vector<std::shared_ptr<CBaseAnimation>> m_animations;
std::vector<Operation> m_pendingOperations;


void CAnimationManager_Update(float dt)
{
    // Handle the deletion list
    for (auto const& operation : m_pendingOperations)
    {
        switch (operation.action)
        {
        case PendingAction::Remove:
            std::cout << "Removing item: " << operation.animation->Name() << std::endl;
            m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), operation.animation), m_animations.end());
            break;
        case PendingAction::Add:
            std::cout << "Adding item: " << operation.animation->Name() << std::endl;
            m_animations.push_back(operation.animation);
            break;
        }
    }
    
    m_pendingOperations.clear();

    // Update the current animation list
    for (auto animation : m_animations)
    {
        if (animation->NeedUpdate() && !animation->GetPaused())
        {
            std::cout << "Updating animation: " << animation->Name() << std::endl;
            animation->Update(dt);
        }
    }
    
    //SetUpdateRequired(NoUpdates);
}

int main()
{
    // Add some dummy animations
    m_animations.push_back(std::make_shared<CBaseAnimation>("1st"));
    m_animations.push_back(std::make_shared<CBaseAnimation>("2nd"));
    m_animations.push_back(std::make_shared<CBaseAnimation>("3rd"));
    m_animations.push_back(std::make_shared<CBaseAnimation>("4th"));
    
    // Add some actions
    m_pendingOperations.push_back({PendingAction::Remove, m_animations[1]});
    m_pendingOperations.push_back({PendingAction::Remove, m_animations[3]});
    m_pendingOperations.push_back({PendingAction::Add, std::make_shared<CBaseAnimation>("5th")});

    CAnimationManager_Update(1.f);
}