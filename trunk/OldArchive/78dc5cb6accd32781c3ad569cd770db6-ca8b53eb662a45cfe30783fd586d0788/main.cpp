/* The top and bottom parts, when commented on and off, make unions explode */
    
    template <class T> 
    struct RVector3 {
	public:
		typedef T TElement;

		/*const static RVector3<T> UnitX;
		const static RVector3<T> UnitY;
		const static RVector3<T> UnitZ;
		const static RVector3<T> Right;
		const static RVector3<T> Up;
		const static RVector3<T> Forward;
		const static RVector3<T> Left;
		const static RVector3<T> Down;
		const static RVector3<T> Backward;
		const static RVector3<T> One;
		const static RVector3<T> Zero;
		const static RVector3<T> MinValue;
		const static RVector3<T> MaxValue;*/

		template <int x> struct ExpandingSwizzler3 {
			struct {
				T v[3];
			};

			ExpandingSwizzler3<x>& operator=(const T& right) {
				v[0] = right;
				v[1] = right;
				v[2] = right;
				return *this;
			}

			operator RVector3 () const {
				RVector3 r = { v[x], v[x], v[x] };
				return r;
			}
		};

		template <int x, int y, int z> struct Swizzler3 {
			struct {
				T v[3];
			};

			Swizzler3<x, y, z>& operator= (const RVector3& right) {
				T ex = right.x;
				T ey = right.y;
				T ez = right.z;
				v[x] = ex;
				v[y] = ey;
				v[z] = ez;
				return *this;
			}

			operator RVector3 () const {
				RVector3 r = { v[x], v[y], v[x] };
				return r;
			}
		};

		union {

			struct {
				T x, y, z;
			};

			struct {
				T r, g, b;
			};

			struct {
				T cell[3];
			};

			ExpandingSwizzler3<0> xxx;
			ExpandingSwizzler3<1> yyy;
			ExpandingSwizzler3<2> zzz;
			Swizzler3<0,0,1> xxy;
			Swizzler3<0,0,2> xxz;
			Swizzler3<0,1,0> xyx;
			Swizzler3<0,1,1> xyy;
			Swizzler3<0,1,2> xyz;
			Swizzler3<0,2,0> xzx;
			Swizzler3<0,2,1> xzy;
			Swizzler3<0,2,2> xzz;
			Swizzler3<1,0,0> yxx;
			Swizzler3<1,0,1> yxy;
			Swizzler3<1,0,2> yxz;
			Swizzler3<1,1,0> yyx;
			Swizzler3<1,1,2> yyz;
			Swizzler3<1,2,0> yzx;
			Swizzler3<1,2,1> yzy;
			Swizzler3<1,2,2> yzz;
			Swizzler3<2,0,0> zxx;
			Swizzler3<2,0,1> zxy;
			Swizzler3<2,0,2> zxz;
			Swizzler3<2,1,0> zyx;
			Swizzler3<2,1,1> zyy;
			Swizzler3<2,1,2> zyz;
			Swizzler3<2,2,0> zzx;
			Swizzler3<2,2,1> zzy;
			
			ExpandingSwizzler3<0> rrr;
			ExpandingSwizzler3<1> ggg;
			ExpandingSwizzler3<2> bbb;
			Swizzler3<0,0,1> rrg;
			Swizzler3<0,0,2> rrb;
			Swizzler3<0,1,0> rgr;
			Swizzler3<0,1,1> rgg;
			Swizzler3<0,1,2> rgb;
			Swizzler3<0,2,0> rbr;
			Swizzler3<0,2,1> rbg;
			Swizzler3<0,2,2> rbb;
			Swizzler3<1,0,0> grr;
			Swizzler3<1,0,1> grg;
			Swizzler3<1,0,2> grb;
			Swizzler3<1,1,0> ggr;
			Swizzler3<1,1,2> ggb;
			Swizzler3<1,2,0> gbr;
			Swizzler3<1,2,1> gbg;
			Swizzler3<1,2,2> gbb;
			Swizzler3<2,0,0> brr;
			Swizzler3<2,0,1> brg;
			Swizzler3<2,0,2> brb;
			Swizzler3<2,1,0> bgr;
			Swizzler3<2,1,1> bgg;
			Swizzler3<2,1,2> bgb;
			Swizzler3<2,2,0> bbr;
			Swizzler3<2,2,1> bbg;
			
		};

		/* SNIP */
        /* Note, there are no constructors. I'm not that dumb. =| */
    };

	template <typename T>
	RVector3<T> operator + (const RVector3<T>& left, const T& right) {
		RVector3<T> r = { left.x + right, left.y + right, left.z + right };
		return r;
	}

	template <typename T>
	RVector3<T> operator - (const RVector3<T>& left, const T& right) {
		RVector3<T> r = { left.x - right, left.y - right, left.z - right };
		return r;
	}

	template <typename T>
	RVector3<T> operator * (const RVector3<T>& left, const T& right) {
		RVector3<T> r = { left.x * right, left.y * right, left.z * right };
		return r;
	}

	template <typename T>
	RVector3<T> operator / (const RVector3<T>& left, const T& right) {
		T invright = 1 / right;
		RVector3<T> r = { left.x * invright, left.y * invright, left.z * invright };
		return r;
	}

	template <typename T>
	RVector3<T> operator + (const T& right, const RVector3<T>& left ) {
		RVector3<T> r = { left.x + right, left.y + right, left.z + right };
		return r;
	}

	template <typename T>
	RVector3<T> operator - (const T& right, const RVector3<T>& left ) {
		RVector3<T> r = { right - left.x, right - left.y, right - left.z };
		return r;
	}

	template <typename T>
	RVector3<T> operator * (const T& right, const RVector3<T>& left ) {
		RVector3<T> r = { left.x * right, left.y * right, left.z * right };
		return r;
	}

	template <typename T>
	RVector3<T> operator / (const T& right, const RVector3<T>& left ) {
		RVector3<T> r = { right / left.x, right / left.y, right / left.z };
		return r;
	}

	/*template<class T> const RVector3<T> RVector3<T>::MaxValue = { Mathema<T>::Maximum, Mathema<T>::Maximum, Mathema<T>::Maximum };
	template<class T> const RVector3<T> RVector3<T>::MinValue = { Mathema<T>::Minimum, Mathema<T>::Minimum, Mathema<T>::Minimum };
	template<class T> const RVector3<T> RVector3<T>::Zero = { 0, 0, 0 };
	template<class T> const RVector3<T> RVector3<T>::UnitX = { 1, 0, 0 };
	template<class T> const RVector3<T> RVector3<T>::UnitY = { 0, 1, 0 };
	template<class T> const RVector3<T> RVector3<T>::UnitZ = { 0, 0, 1 };
	template<class T> const RVector3<T> RVector3<T>::Right = { 1, 0, 0 };
	template<class T> const RVector3<T> RVector3<T>::Up = { 0, 1, 0 };
	#ifdef FURROVINECOORDINATESYSTEM_LEFTHANDED
	template<class T> const RVector3<T> RVector3<T>::Forward = { 0, 0, 1 };
	template<class T> const RVector3<T> RVector3<T>::Backward = { 0, 0, -1 };
	#else
	template<class T> const RVector3<T> RVector3<T>::Forward = { 0, 0, -1 };
	template<class T> const RVector3<T> RVector3<T>::Backward = { 0, 0, 1 };
	#endif
	template<class T> const RVector3<T> RVector3<T>::Left = { -1, 0, 0 };
	template<class T> const RVector3<T> RVector3<T>::Down = { 0, -1, 0 };
	template<class T> const RVector3<T> RVector3<T>::One = { 1, 1, 1 };*/


int main (int, char*[] ) {
    RVector3<float> arf = { 1, 1, 1 };
    arf.x *= 2;
}