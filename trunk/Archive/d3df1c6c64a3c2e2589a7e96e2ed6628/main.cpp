#ifndef FURROVINERVECTOR2_H
#define FURROVINERVECTOR2_H

#include <Furrovine++/Core.h>

namespace Furrovine {
    
	template <class T> struct RVector2 {
	public:
		typedef T TElement;

		template <int x> struct ExpandingSwizzler2 {
			struct {
				T v[2];
			};

			ExpandingSwizzler2<x>& operator=(const T& right) {
				v[0] = right;
				v[1] = right;
				return *this;
			}

			operator RVector2<T> () const {
				RVector2<T> r = { v[x], v[x] };
				return r;
			}
		};

		template <int x, int y> struct Swizzler2 {
			struct {
				T v[2];
			};

			Swizzler2<x, y>& operator= (const RVector2<T>& right) {
				T ex = right.x;
				T ey = right.y;
				v[x] = ex;
				v[y] = ey;
				return *this;
			}

			operator RVector2<T> () const {
				RVector2<T> r = { v[x], v[y] };
				return r;
			}
		};

		union {

			struct {
				T x, y;
			};

			struct {
				T u, v;
			};

			T cell[2];

			ExpandingSwizzler2<0> xx;
			ExpandingSwizzler2<1> yy;
			Swizzler2<0, 1> xy;
			Swizzler2<1, 0> yx;

			ExpandingSwizzler2<0> uu;
			ExpandingSwizzler2<1> vv;
			Swizzler2<0, 1> uv;
			Swizzler2<1, 0> vu;
		};

		T Length () const {
			return Mathema<T>::Sqrt(x * x + y * y);
		}

		T LengthSquared () const {
			return x * x + y * y;
		}

		T DistanceTo (const RVector2<T>& to) const {
			T tx = to.x - x;
			T ty = to.y - y;
			return Mathema<T>::Sqrt(tx * tx + ty * ty);
		}

		T DistanceToSquared (const RVector2<T>& to) const {
			T tx = to.x - x;
			T ty = to.y - y;
			return tx * tx + ty * ty;
		}

		RVector2<T> Direction (const RVector2<T>& to) const {
			RVector2<T> direction = to - *this;
			direction.Normalize();
			return direction;
		}

		T Dot (const RVector2<T>& right) const {
			return x * right.x + y * right.y;
		}

		T Angle (const RVector2<T>& right) const {
			return Mathema<T>::Acos(Dot(right) / (Length() * right.Length()));
		}

		RVector2<T>& Normalize () {
			T len = x * x + y * y;
			if (len != 0 && len != 1) {
				len = Mathema<T>::Sqrt(len);
				x /= len;
				y /= len;
			}
			return *this;
		}

		RVector2<T> Normalization () const {
			T len = x * x + y * y;
			RVector2<T> r = {x , y};
			if (len != 0 && len != 1) {
				len = Mathema<T>::Sqrt(len);
				r.x /= len;
				r.y /= len;
			}
			return r;
		}

		T Cross (const RVector2<T>& right) const {
			return x * right.y - right.x * y;
		}

		RVector2<T> Lerp (const RVector2<T>& towards, float weight) const {
			weight = Mathema<float>::MiniMax(weight, 0.0f, 1.0f);
			float affweight = 1.0f - weight;
			RVector2<T> r = {
				castto(T, x * affweight + weight * towards.x),
				castto(T, y * affweight + weight * towards.y) };
			return r;
		}

		RVector2<T> Max (const RVector2<T>& b) const {
			RVector2<T> r = {Mathema<T>::Max(x, b.x), Mathema<T>::Max(y, b.y)};
			return r;
		}

		RVector2<T> Min (const RVector2<T>& b) const {
			RVector2<T> r = { Mathema<T>::Min(x, b.x), Mathema<T>::Min(y, b.y) };
			return r;
		}

		RVector2<T>& Maximize (const RVector2<T>& b) {
			x = Mathema<T>::Max(x, b.x);
			y = Mathema<T>::Max(y, b.y);
			return *this;
		}

		RVector2<T>& Minimize (const RVector2<T>& b) {
			x = Mathema<T>::Min(x, b.x);
			y = Mathema<T>::Min(y, b.y);
			return *this;
		}

		int Quadrant () const {
			int quad = 0;
			quad |= ((x >= 0));
			quad |= ((y >= 0) << 1);
			return quad;
		}

		int Quadrant (const RVector2<T>& origin) const {
			int quad = 0;
			quad |= ((x >= origin.x));
			quad |= ((y >= origin.y) << 1);
			return quad;
		}

		bool QuadrantChange ( const RVector2<T>& after, const RVector2<T>& origin ) const {
			RVector2<T> bOrigin = *this - origin;
			RVector2<T> aOrigin = after - origin;

			return ( !( (aOrigin.x > 0) == (bOrigin.x > 0) ) ||
				!( (aOrigin.y > 0) == (bOrigin.y > 0) ) )
				// Quadrant has changed
				;
		}

		bool QuadrantChange ( const RVector2<T>& after ) const {
			return ( !( (after.x > 0) == (x > 0) ) ||
				!( (after.y > 0) == (y > 0) ) )
				// Quadrant has changed
				;
		}

		bool IsUnit () const {
			return ( x * x + y * y ) == 1;
		}

		RVector2<T>& operator= (const RVector2<T>& right) {
			x = right.x;
			y = right.y;
			return *this;
		}

		RVector2<T>& operator-= (const RVector2<T>& right) {
			x -= right.x;
			y -= right.y;
			return *this;
		}

		RVector2<T>& operator+= (const RVector2<T>& right) {
			x += right.x;
			y += right.y;
			return *this;
		}

		RVector2<T>& operator*= (const RVector2<T>& right) {
			x *= right.x;
			y *= right.y;
			return *this;
		}

		RVector2<T>& operator/= (const RVector2<T>& right) {
			x /= right.x;
			y /= right.y;
			return *this;
		}

		RVector2<T>& operator*= (const T& right) {
			x *= right;
			y *= right;
			return *this;
		}

		RVector2<T>& operator/= (const T& right) {
			T invright = 1 / right;
			x *= invright;
			y *= invright;
			return *this;
		}

		RVector2<T>& operator++ () {
			++x;
			++y;
			return *this;
		}

		RVector2<T>& operator-- () {
			--x;
			--y;
			return *this;
		}

		RVector2<T> operator++ (int) {
			RVector2<T> r = {x++, y++};
			return r;
		}

		RVector2<T> operator-- (int) {
			RVector2<T> r = {x--, y--};
			return r;
		}

		RVector2<T> operator- (const RVector2<T>& right) const {
			RVector2<T> r = {x - right.x, y - right.y};
			return r;
		}

		RVector2<T> operator+ (const RVector2<T>& right) const {
			RVector2<T> r = {x + right.x, y + right.y};
			return r;
		}

		RVector2<T> operator* (const RVector2<T>& right) const {
			RVector2<T> r = {x * right.x, y * right.y};
			return r;
		}

		RVector2<T> operator/ (const RVector2<T>& right) const {
			RVector2<T> r = {x / right.x, y / right.y};
			return r;
		}

		RVector2<T> operator* (const T& right) const {
			RVector2<T> r = {x * right, y * right};
			return r;
		}

		RVector2<T> operator/ (const T& right) const {
			T invright = 1 / right;
			RVector2<T> r = {x * invright, y * invright};
			return r;
		}

		RVector2<T> operator+ () const {
			RVector2<T> r = {+x, +y};
			return r;
		}

		RVector2<T> operator- () const {
			RVector2<T> r = {-x, -y};
			return r;
		}

		bool operator== (const RVector2<T>& right) const {
			return right.x == x && right.y == y;
		}

		bool operator!= (const RVector2<T>& right) const {
			return right.x != x || right.y != y;
		}

		operator T* () {
			return (T*)cell;
		}

		operator T* () const {
			return (T*)cell;
		}

		T& operator[] (int index) {
			return cell[index];
		}

		T& operator[] (int index) const {
			return *(T*)( cell + index );
		}

		template <typename TCast> operator RVector2<TCast> () const {
			RVector2<TCast> r = { (TCast)x, (TCast)y };
			return r;
		}

		static RVector2<T> Direction (const RVector2<T>& from, const RVector2<T>& to) {
			RVector2<T> direction = to - from;
			direction.Normalize();
			return direction;
		}

		static T Dot (const RVector2<T>& left, const RVector2<T>& right) {
			return left.x * right.x + left.y * right.y;
		}

		static T Cross (const RVector2<T>& left, const RVector2<T>& right) {
			return left.x * right.y - right.x * left.y;
		}

		static RVector2<T> Normalize (const T& x, const T& y) {
			T len = x * x + y * y;
			RVector2<T> r = {x, y};
			if (len != 0 && len != 1) {
				len = Mathema<T>::Sqrt(len);
				r.x /= len;
				r.y /= len;
			}
			return r;
		}

		static RVector2<T> Normalize (const RVector2<T>& vec) {
			T len = vec.LengthSquared();
			RVector2<T> r = {vec.x, vec.y};
			if (len != 0 && len != 1) {
				len = Mathema<T>::Sqrt(len);
				r.x /= len;
				r.y /= len;
			}
			return r;
		}

		static T Angle (const RVector2<T>& left, const RVector2<T>& right) {
			return Mathema<T>::Acos(left.Dot(right) / (left.Length() * right.Length()));
		}

		static bool QuadrantChange ( const RVector2<T>& before, const RVector2<T>& after, const RVector2<T>& origin ) {
			RVector2<T> bOrigin = before - origin;
			RVector2<T> aOrigin = after - origin;

			return ( !( (aOrigin.x > 0) == (bOrigin.x > 0) ) ||
				!( (aOrigin.y > 0) == (bOrigin.y > 0) ) )
				// Quadrant has changed
				;
		}

		static RVector2<T> Max (const RVector2<T>& a, const RVector2<T>& b) {
			RVector2<T> r = { Mathema<T>::Max(a.x, b.x), Mathema<T>::Max(a.y, b.y) };
			return r;
		}

		static RVector2<T> Min (const RVector2<T>& a, const RVector2<T>& b) {
			RVector2<T> r = { Mathema<T>::Min(a.x, b.x), Mathema<T>::Min(a.y, b.y) };
			return r;
		}
	};

}
#endif /* FURROVINERVECTOR2_H */
