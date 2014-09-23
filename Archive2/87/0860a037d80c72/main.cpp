#include <map>
#include <memory>
#include <tuple>

struct SceneNode {};

int main()
{
    std::multimap<unsigned int, std::shared_ptr<SceneNode>> subnodes_m;
    
    unsigned int layerIndex = 1;
    SceneNode* subnode_p = new SceneNode;
    
    // std::pair<unsigned int, std::shared_ptr<SceneNode>> p( 1, subnode_p ); // error!
    
    subnodes_m.emplace(1, std::shared_ptr<SceneNode>(subnode_p));
    
    subnodes_m.emplace(std::piecewise_construct
                     , std::forward_as_tuple(1)
                     , std::forward_as_tuple(subnode_p));
}
