Vec3<double> inferRayDirection(const Vec2<double>& pixel) const restrict(cpu, amp) {
    auto direction = pixel.x * cameraX + pixel.y * cameraY - viewPlaneDistance * cameraZ;
    direction.normalize();
    return direction;
}

Ray Compute( real x, real y, real width, real height ) const {
	real normalizedi = ( x / width ) - static_cast<real>( 0.5 );
	real normalizedj = ( y / height ) - static_cast<real>( 0.5 );
	normalizedi *= width;
	normalizedj *= height;
	Vec3 imageplanepoint = normalizedi * right +
		normalizedj * up +
		position + direction;
	Vec3 raydir = imageplanepoint - position;
	raydir.normalize( );
	return Ray( position, raydir );
}