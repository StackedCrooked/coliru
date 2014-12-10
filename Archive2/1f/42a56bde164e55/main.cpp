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
    
    void MarkForDeletion() { m_needsDelete = true; }
    bool NeedsDeletion() const { return m_needsDelete; }
    
private:
    std::string m_name;
    bool m_needsDelete{};
};

std::vector<std::shared_ptr<CBaseAnimation>> m_animations;


void CAnimationManager_Update(float dt)
{
    // Update the current animation list
    for (auto it = m_animations.begin(); it != m_animations.end();)
    {
        auto anime = *it;
        
        if (anime->NeedsDeletion())
        {
            std::cout << "Deleting animation: " << anime->Name() << std::endl;
            it = m_animations.erase(it);
            continue;
        }
        else if (anime->NeedUpdate() && !anime->GetPaused())
        {
            std::cout << "Updating animation: " << anime->Name() << std::endl;
            anime->Update(dt);
        }
        
        ++it;
    }
    
    //SetUpdateRequired(NoUpdates);
}

void CAnimationManager_Add(std::shared_ptr<CBaseAnimation> anime)
{
    std::cout << "Adding animation: " << anime->Name() << std::endl;
    m_animations.push_back(anime);
}

void CAnimationManager_Remove(std::shared_ptr<CBaseAnimation> anime)
{
    std::cout << "Scheduling animation to be deleted: " << anime->Name() << std::endl;
    anime->MarkForDeletion();
}

int main()
{
    // Add some dummy animations
    m_animations.push_back(std::make_shared<CBaseAnimation>("1st"));
    m_animations.push_back(std::make_shared<CBaseAnimation>("2nd"));
    m_animations.push_back(std::make_shared<CBaseAnimation>("3rd"));
    m_animations.push_back(std::make_shared<CBaseAnimation>("4th"));
    
    // Add some actions
    CAnimationManager_Remove(m_animations[1]);
    CAnimationManager_Remove(m_animations[3]);
    CAnimationManager_Add(std::make_shared<CBaseAnimation>("5th"));

    CAnimationManager_Update(1.f);
}