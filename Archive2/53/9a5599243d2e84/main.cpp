#include <cassert>
#include <string>
#include <vector>

typedef double Vector3;
typedef double Matrix;
typedef double Quaternion;
typedef std::size_t ulword;

template <typename value_type, typename time_type = double>
    struct TimeValue {
		typedef time_type TTime;
		typedef value_type TValue;
		static const TTime Epsilon;
		TTime time;
		TValue value;

		bool operator == ( const TimeValue& obj ) const {
			return time == obj.time;
		}

		bool operator != ( const TimeValue& obj ) const {
			return time != obj.time;
		}

		bool operator < ( const TimeValue& obj ) const {
			return time < obj.time;
		}

		bool operator > ( const TimeValue& obj ) const {
			return time > obj.time;
		}
	};

struct SkeletalAnimationChannel {    
    public:
    	typedef TimeValue<Vector3> TranslationKey;
		typedef TimeValue<Vector3> ScaleKey;
		typedef TimeValue<Quaternion> RotationKey;
		typedef TimeValue<Matrix> TransformKey;

	private:
		Matrix transformmatrix;
		std::string name;
		ulword lasttranslationindex;
		ulword lastscalingindex;
		ulword lastrotationindex;
		double duration;
		double currenttime, lasttime;
		std::vector<TransformKey> transformkeys;

	public:
        SkeletalAnimationChannel() {}
        SkeletalAnimationChannel ( SkeletalAnimationChannel&& ) = default;
        SkeletalAnimationChannel& operator=(SkeletalAnimationChannel&&) = default;

};

struct Container {
    std::string name;
    double duration;
    std::vector<SkeletalAnimationChannel> arf;
    
    Container() {}
    Container( Container&& ) = default;
    Container& operator=( Container&& ) = default;
    
};

int main () {
    Container no_copy_move_elision{};
    Container c = std::move( no_copy_move_elision );
}