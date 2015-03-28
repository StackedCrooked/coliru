template <typename T>
optional<THit3<T>> intersect( const TRay3<T>& ray, const RPlane<T>& target ) {
    T distance;
	T denom = dot( target.normal, ray.direction );
	if ( denom <= static_cast<T>( 1e-6 ) )
		return nullopt;
	Vec3 onplane = ( target.normal * target.distance );
	Vec3 origindirection = onplane - ray.origin;
	distance = dot( origindirection, target.normal ) / denom;
	if ( distance < 0 )
		return nullopt;

	THit3<T> hit;
	hit.distance0 = distance;
	hit.contact = ray.at( hit.distance0 );
	hit.normal = target.normal;
	return hit;
}