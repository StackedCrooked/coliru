#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/algorithm/string/predicate.hpp>

struct Model
{
    Model(const std::string& name) : name(name) {};
    std::string mName() const
    {
        return name;
    }
    
private:
    std::string name;
};

int main()
{
    std::vector<Model> mModels;
    mModels.push_back(Model("a"));
    mModels.push_back(Model("b"));
    mModels.push_back(Model("c"));
    
    const std::string assetName = "B";
    
    std::vector<Model>::iterator it = std::find_if(
        mModels.begin(),
        mModels.end(),
        boost::bind(
            &boost::iequals<std::string,std::string>,
            boost::bind(&Model::mName, _1),
            assetName,
            std::locale()
        )
    );
    
    assert(it != mModels.end());
    std::cout << it->mName() << std::endl; // expected: "b"
}
