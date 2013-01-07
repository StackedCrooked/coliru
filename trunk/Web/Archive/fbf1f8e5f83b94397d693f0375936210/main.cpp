RVector4<T> r = {x + right.x, y + right.y, z + right.z, w + right.w};
// or ?
RVector4<T> r; 
for ( int i = 0; i < 4; ++i )
	r.cell[i] = cell[i] + right.cell[i];

// Which do?
			