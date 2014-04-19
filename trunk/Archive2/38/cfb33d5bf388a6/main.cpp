#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>
#include <sstream>
#include <fstream>

namespace ORROctree
{
    struct Node
    {
        struct Data {
            int id_x_, id_y_, id_z_;
            int neighbors_, lin_id_, num_points_;
            int p_;
        };
        Data data_;
        int center_, bounds_, radius_;
        
        Node* parent_;
        std::vector<Node*> children_; 
    };
}

using std::string;

struct ModelLibrary {

    template <typename T> struct NDIMVoxelStructure {
        int voxels_[12]          = {};
        int total_num_of_voxels_ = 12;
        int num_of_voxels_       = 0;
        int bounds_              = 0;
        int spacing_             = 0;
        int min_center_          = 0;
    };

    typedef std::pair<const ORROctree::Node::Data*, const ORROctree::Node::Data*> Dipole;
    struct Base {
        Dipole seg1;
        Dipole seg2;
    };
    typedef std::list<Base> bases_list;
    typedef std::map <string, bases_list> SerializeHashTableCell;
    typedef NDIMVoxelStructure<SerializeHashTableCell> SerializeHashTable;

    public:
    bool saveHashTable();

    bool loadHashTable();

    virtual bool generateHashTableArchiveName (string &filename) = 0;

    public:
    SerializeHashTable shash_table_;  /***** MEMBER TO BE SERIALIZED ******/
};

// SERIALIZATION METHODS FOR THE TYPES USED TO FORM THE SERIALIZEHASHTABLE
namespace boost {
    namespace serialization {

        template<class Archive>
            inline void serialize(Archive & ar, ModelLibrary::SerializeHashTable & h, const unsigned int version)
            {
                ar & boost::serialization::make_array(h.voxels_, h.total_num_of_voxels_); 
                ar & h.num_of_voxels_;
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
    } // namespace serialization
} // namespace boost

bool ModelLibrary::saveHashTable ()
{
    string filename;
    generateHashTableArchiveName (filename);
    std::cout << "archive filename" << filename;
    std::ofstream ofs(filename.c_str());
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << shash_table_;
    // archive and stream closed when destructors are called
    return true;
}


bool
ModelLibrary::loadHashTable ()
{
    string filename;
    generateHashTableArchiveName (filename);
    std::ifstream ifs(filename.c_str());
    boost::archive::text_iarchive ia(ifs);
    ia >> shash_table_;
    return true;
}

//Derived.h
class ModelLibraryG4PCS: public ModelLibrary
{
    int pair_width_, dipole_width_, voxel_size_;
    typedef ModelLibraryG4PCS Model;
    std::map<std::string, Model*> models_;
    virtual bool generateHashTableArchiveName (string &filename);
};

//Derived.cpp
    bool
ModelLibraryG4PCS::generateHashTableArchiveName (string &filename)
{
    filename = "";
    //Concatenate all Added Models into filename
    std::map<std::string, Model*>::const_iterator model_itr = models_.begin();
    for (; model_itr != models_.end(); ++model_itr)
    {
        filename += model_itr->first;
    }

    // No Models Have been added
    if (filename == "")
        return false;

    std::stringstream ss;
    ss << pair_width_ << "_" << dipole_width_ << "_" << voxel_size_ << ".hash";
    filename += ss.str();
    return true;
}

//main.cpp
int main() 
{
    ModelLibraryG4PCS d;
    if (!d.loadHashTable()) {
        /* Some Code to Construct a new Hash Table */
        d.saveHashTable();
    }
}
