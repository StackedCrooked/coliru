#include<vector>
#include<array>
#include<iostream>
#include<algorithm>

// deletes the elements from container c1 which are also present in c2
// requires sorted containers c1 and c2
//
template< class ContainerType1, class ContainerType2 >
void delete_common_elements(ContainerType1& c1, ContainerType2 const& c2 )
{
    for(auto it1=c1.begin(), it2=c2.begin()
      ; it1!=c1.end() && it2!=c2.end()
      ; *it1<*it2 ? ++it1 : ++it2)
    {
        if(*it1==*it2)
        {
            c1.erase(it1);
        }
    }
}                       

int main()
{
    std::vector<std::array<int,3> > objPoints = {{1,1,1}, {2,3,5}, {8,9,11}};
    std::vector<std::array<int,3> > delPoints = {{1,1,1}, {8,9,11}};

    std::sort(objPoints.begin(),objPoints.end());
    std::sort(delPoints.begin(),delPoints.end());

    delete_common_elements(objPoints, delPoints);

    for(auto v : objPoints)
    {
        std::cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;
    }
}
    