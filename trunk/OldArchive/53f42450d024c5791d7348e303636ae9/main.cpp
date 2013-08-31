template <typename TVertex> 
    void GraphicsDevice::RenderUserPrimitives ( PrimitiveTopology primitive, const VertexDeclaration& declaration, TVertex* vertices, int vertexoffset, int primitivecount ) {
		VertexBuffer* vbuffer = null;
		IndexBuffer* ibuffer = null;
		ulword ivindex;
		Type vtype = typeof<TVertex>( );

		if ( !instantindices.TryGetValue( vtype, ivindex ) ) {
			ivindex = instantvtxbuffers.Count();
			vbuffer = new VertexBuffer( *this, ResourceUsage::Dynamic, CpuAccessFlags::Writable );
			ibuffer = new IndexBuffer( *this, ResourceUsage::Dynamic, CpuAccessFlags::Writable );
			instantindices.Add( vtype, ivindex );
			instantvtxbuffers.Add( vbuffer );
			instantidxbuffers.Add( ibuffer );
		}
		else {
			vbuffer = instantvtxbuffers[ivindex];
			ibuffer = instantidxbuffers[ivindex];
		}

		int vertexcount = Primitives::VertexCount( primitive, primitivecount );
		vbuffer->SetData( vertices, vertexcount );
		ID3D11Buffer* internalvbuffer = null;
		uint stride, offset;
		devicecontext->IAGetVertexBuffers( activevb, 1, &internalvbuffer, &stride, &offset );

		bool resetvbuffer = vbuffer->gpubuffer.get() != internalvbuffer;
		if ( resetvbuffer ) {
			SetVertexBuffer( activevb, *vbuffer );
			resetvbuffer = internalvbuffer != null;
		}

		RenderPrimitives( primitive, vertexoffset, primitivecount );

		if ( resetvbuffer ) {
			devicecontext->IASetVertexBuffers( activevb, 1, &internalvbuffer, &stride, &offset );
		}
	}