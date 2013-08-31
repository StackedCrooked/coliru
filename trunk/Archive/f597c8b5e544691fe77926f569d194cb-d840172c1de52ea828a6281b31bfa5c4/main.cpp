int main ( int argc, char* argv[] ) {
    std::vector<Vector3> positions;
    std::vector<Vector2> textures;
    std::vector<Vector3> normals;
    std::vector<uint32> positionindices;
    std::vector<uint32> textureindices;
    std::vector<uint32> normalindices;
    int32 posidx;
    int32 texidx;
    int32 normalidx;
    uint32 idx;
    // Insert blank-state numbers for when there is no index in the declarations,
    // eg a face with: `f 1//1 2//2 3//3` (missing texture coordinate index)
    // OBJ is also 1-based, so we can always assume that 0 is a safe
    // index to use for the "non-existent" state
    positions.push_back( Vector3::Zero );
    textures.push_back( Vector2::Zero );
    normals.push_back( Vector3::Zero );
    
    // Blah blah blah, forward-only parsing
    // During the reading, we immediately convert negative
    // integers to their unsigned representation at the time,
    // so that our 3 individual indices streams contain the absolute position in the vertices
    /* ... */
    reader.ReadInt32( posidx );
	if ( posidx < 0 )
		posidx = (int32)context.positions.size() + posidx;
	tempvector3 = context.positions[ posidx ];
	Vector3::Max( context.partmax, tempvector3, context.partmax );
	Vector3::Min( context.partmin, tempvector3, context.partmin );
	reader.SkipBlankSpace( );
	if ( reader.Peek( ) == '/' ) {
		reader.Read( );
		if ( reader.Peek( ) == '/' ) {
			reader.Read( );
			reader.ReadInt32( normidx );
			if ( normidx < 0 )
				normidx = (int32)context.normals.size() + normidx;
			texidx = 0;
			reader.SkipBlankSpace( );
		}
		else {
			reader.ReadInt32( texidx );
			if ( texidx < 0 )
				texidx = (int32)context.textures.size() + texidx;
			reader.SkipBlankSpace( );
			if ( reader.Peek( ) == '/' ) {
				reader.Read( );
				reader.ReadInt32( normidx );
				if ( normidx < 0 )
					normidx = (int32)context.normals.size() + normidx;
				reader.SkipBlankSpace( );
			}
			else {
				normidx = 0;
				makenormals |= true;
			}
		}
	}
	else {
		texidx = 0;
		normidx = 0;
		makenormals |= true;
	}  
    // No we do some gluing and adding,
    // expanding faces for triangluation purposes
    if ( idx < 3 ) {
		context.positionsindices.push_back( posidx );
		context.normalsindices.push_back( normidx );
		context.texturesindices.push_back( texidx );
		++idx;
	}
	else {
		count = (int32)context.positionsindices.size();
		start = count - idx;
		--count;
		context.positionsindices.push_back( context.positionsindices[ start ] );
		context.positionsindices.push_back( context.positionsindices[ count ] );
		context.positionsindices.push_back( posidx );
		context.normalsindices.push_back( context.normalsindices[ start ] );
		context.normalsindices.push_back( context.normalsindices[ count ] );
		context.normalsindices.push_back( normidx );
		context.texturesindices.push_back( context.texturesindices[ start ] );
		context.texturesindices.push_back( context.texturesindices[ count ] );
		context.texturesindices.push_back( texidx );
		idx += 3;
	}
    // One way to eliminate the above is to see if you can make a fast hash_map for each triple,
    // and build a list of indices while also building a list of vertices on-the-fly
    /* ... */
    
    // Supported, but OBJs shouldn't be used to only specify normals and textures, unless
    // there's some kind of we-already-got-the-vertices contract between
    // the loader and the user
    if ( positionindices.size() < normalindices.size() || positionindices.size() < textureindices.size() )
        log_warning( "Uh. This is an ill-formed OBJ file. Just letting you know..." );
    
    // Now, we glue them together
    // This is the case where we don't want to deal with making an index buffer
    // If we do make an index buffer, we have to manually build a list of repeating triples,
    // or we store the vertex attributes in separate streams, old-OpenGL style
    uint32 size = max( max( positionindices.size(), normalindices.size() ), textureindices.size() );
    
    //for ( auto v : /* ... what do? The indices come from 3 different attribute streams */ ) 
    for ( uint32 v = 0; v < size; ++v ) {
        context.vertices.emplace_back( 
            context.positions[ context.positionsindices[ v ] ], 
            context.textures[ context.texturesindices[ v ] ], 
            context.normals[ context.normalsindices[ v ] ] );
    }
}