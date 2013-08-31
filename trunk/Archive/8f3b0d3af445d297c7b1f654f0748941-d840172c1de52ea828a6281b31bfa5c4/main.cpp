template <typename TVertex> 
void SetData ( const std::vector<TVertex>& vertices, uint32 stream = 0 );
template <typename TVertex> 
void SetData ( const TVertex* const vertices, int32 count, uint32 stream = 0 );
template <typename TVertex> 
void SetData ( const TVertex* const vertices, int32 count, const VertexDeclaration* declaration, uint32 stream = 0 );
// An iterator version would be nice, I guess?