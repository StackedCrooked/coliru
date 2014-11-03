#include <boost/serialization/access.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

class StartPeerSessionRequest {
public:
    StartPeerSessionRequest();
    virtual ~StartPeerSessionRequest() {}
    void save();
    std::stringstream serializedRequest;
    /*boost::serialization::binary_object serlreq;*/

private:
    StartPeerSessionRequest(const StartPeerSessionRequest &);

    uint16_t mProtocolVersion;
    uint16_t mSessionFlags;
    uint16_t mMaxResponseLength;
    std::string   mMake;
    std::string   mModel;
    std::string   mSerialNumber;
    uint8_t  mTrackDelay;
    std::string   mHeadUnitModel;
    std::string   mCarModelYear;
    std::string   mVin;
    uint16_t mVehicleMileage;
    uint8_t  mShoutFormat;
    uint8_t  mNotificationInterval;

    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive &ar, const unsigned int version);
};

StartPeerSessionRequest::StartPeerSessionRequest() {

    mProtocolVersion      = 1 * 10000 + 14 * 100 + 4;
    mSessionFlags         = 1;
    mMaxResponseLength    = 0;
    mMake                 = "MyMake";
    mModel                = "MyModel";
    mSerialNumber         = "10000";
    mTrackDelay           = 0;
    mHeadUnitModel        = "Headunit";
    mCarModelYear         = "2014";
    mVin                  = "1234567980";
    mVehicleMileage       = 1000;
    mShoutFormat          = 3;
    mNotificationInterval = 1;
}

template <class Archive> void StartPeerSessionRequest::serialize(Archive &ar, const unsigned int version) {
    ar & mProtocolVersion;
    ar & mSessionFlags;
    ar & mMaxResponseLength;
    ar & mMake;
    ar & mModel;
    ar & mSerialNumber;
    ar & mTrackDelay;
    ar & mHeadUnitModel;
    ar & mCarModelYear;
    ar & mVin;
    ar & mVehicleMileage;
    ar & mShoutFormat;
    ar & mNotificationInterval;
}

// elminate serialization overhead at the cost of
// never being able to increase the version.
BOOST_CLASS_IMPLEMENTATION(StartPeerSessionRequest, boost::serialization::object_serializable)

// eliminate object tracking (even if serialized through a pointer)
// at the risk of a programming error creating duplicate objects.
BOOST_CLASS_TRACKING(StartPeerSessionRequest, boost::serialization::track_never)


void StartPeerSessionRequest::save() {
    boost::archive::text_oarchive ota(serializedRequest, boost::archive::no_header|boost::archive::no_tracking);
    ota << const_cast<StartPeerSessionRequest const&>(*this);
    std::cout << "\n text_oarchive :" << serializedRequest.str() << "size :" << serializedRequest.str().size();
}

int main()
{
    StartPeerSessionRequest spsr;
	std::ostringstream ss;
	boost::archive::binary_oarchive oa(ss, boost::archive::archive_flags::no_header|boost::archive::archive_flags::no_tracking);

	oa << spsr;

	std::cout << "Size: " << ss.str().length() << "\n";

	spsr.save();
}