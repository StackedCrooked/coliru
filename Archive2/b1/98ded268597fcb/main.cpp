

class SSet
{
public:
        SSet();

        double m_par1;
        int m_par2;
        QString m_par3;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);
       
};

template<class Archive>
 void SSet::serialize(Archive & ar, const unsigned int version)
 {
    boost::serialization::split_free(ar, m_par3, version);
    ar & BOOST_SERIALIZATION_NVP(m_par1);    
    ar & BOOST_SERIALIZATION_NVP(m_par2);

 }


template<class Archive, class T>
inline void serialize(
    Archive & ar, 
    T & t, 
    const unsigned int file_version
){
    // invoke member function for class T
    t.serialize(ar, file_version);
}
