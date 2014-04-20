#include <map>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>

using namespace std;

struct ORROctree
{
    public:
        struct Node
        {
            public:
                struct Data
                {               
                    Data() : id_x_(0), id_y_(0), id_z_(0), lin_id_(0), num_points_(0), user_data_(0)
                    {
                        std::fill(n_, n_+3, 0);
                        std::fill(p_, p_+3, 0);
                    }
                    public:
                        float n_[3], p_[3];
                        int id_x_, id_y_, id_z_, lin_id_, num_points_;
                        std::set<Node*> neighbors_;
                        void *user_data_;
                };

            public: 
                Node() : data_(0), radius_(0), parent_(0), children_(0) 
                {
                    std::fill(center_, center_+3, 0);
                    std::fill(bounds_, bounds_+6, 0);
                }

                Node::Data *data_;
                float center_[3], bounds_[6], radius_;
                Node *parent_, *children_;
        };        
    protected:
        ORROctree() : voxel_size_(0), tree_levels_(0), root_(0)
        {
            std::fill(bounds_, bounds_+6, 0);
        }
        float voxel_size_, bounds_[6];
        int tree_levels_;
        Node* root_;
        std::vector<Node*> full_leaves_;                  
};

struct ModelLibrary
{  
    template <typename T, typename REAL = float>    
        struct NDIMVoxelStructure 
        {
            NDIMVoxelStructure() : voxels_(0), total_num_of_voxels_(0) 
            {
            }

            T *voxels_;        
            std::vector<int> total_num_of_voxels_i_;
            std::vector<int> num_of_voxels_;
            long total_num_of_voxels_;
            std::vector<REAL> bounds_;
            std::vector<REAL> spacing_; 
            std::vector<REAL> min_center_;
        };


    typedef std::pair<const ORROctree::Node::Data*, const ORROctree::Node::Data*>  Dipole;
    struct Base {
        Base() : seg1(0, 0), seg2(0, 0) 
        {
        }

        Dipole seg1;
        Dipole seg2;
    };
    typedef std::list<Base> bases_list;
    typedef std::map <string, bases_list> SerializeHashTableCell;
    // MEMBER TO BE SERIALIZED
    typedef NDIMVoxelStructure<SerializeHashTableCell> SerializeHashTable;

  public:
    SerializeHashTable shash_table_;

  public:
    bool saveHashTable();

    bool loadHashTable();
};



// SERIALIZATION METHODS FOR THE TYPES USED TO FORM THE SERIALIZEHASHTABLE

namespace boost {
    namespace serialization {

        template<class Archive>
            inline void serialize(Archive & ar, ModelLibrary::SerializeHashTable & h, const unsigned int version)
            {
                ar & h.total_num_of_voxels_;
                ar & boost::serialization::make_array(h.voxels_, h.total_num_of_voxels_);
                ar & h.num_of_voxels_;
                ar & h.total_num_of_voxels_i_;
                ar & h.bounds_;
                ar & h.spacing_;
                ar & h.min_center_;
            }


        template<class Archive>
            inline void serialize(Archive & ar, ModelLibrary::Base & b, const unsigned int version)
            {
                ar & b.seg1;
                ar & b.seg2;
            }


        template<class Archive>
            inline void serialize(Archive & ar, ORROctree::Node n, const unsigned int version)
            {
                ar & n.data_;
                ar & n.center_;
                ar & n.bounds_;
                ar & n.radius_;
                ar & n.parent_;
                ar & n.children_;
            }

        template<class Archive>
            inline void serialize(Archive & ar, ORROctree::Node::Data d, const unsigned int version)
            {
                ar & d.id_x_;
                ar & d.id_y_;
                ar & d.id_z_;
                ar & d.neighbors_;
                ar & d.lin_id_;
                ar & d.num_points_;
                ar & d.p_;
            }
    }
}

bool ModelLibrary::saveHashTable ()
{
    std::ofstream ofs("test.txt");
    boost::archive::text_oarchive oa(ofs);
    oa << shash_table_;
    return true;
}


bool ModelLibrary::loadHashTable ()
{
    std::ifstream ifs("test.txt");
    boost::archive::text_iarchive ia(ifs);
    ia >> shash_table_;
    return true;
}


int main() 
{
    ModelLibrary m;
    m.saveHashTable();
}
