struct GraphicsCapability {
    	Shading::ShaderVersion MaxShader;
		bool GeometryShader;
		bool StreamOutput;
		bool ComputerShader;
		bool HullDomainShader;
		bool TextureResourceArrays;
		bool CubemapResourceArrays;
		bool BC4BC5Compression;
		bool BC6HBC7Compression;
		bool AlphaToCoverage;
		bool ExtendedFormats;
		bool XRHighColor10bitFormat;
		bool LogicOperationsonOutputMerger;
		bool TargetIndependentRasterization;
		bool MultipleRenderTargetsWithForcedSampleCount;
		uint32 UAVSlots;
		bool PerStageUAVs;
		int MaxForcedSampleCountforUAV;
		uint32 ConstantBufferOffsettingandPartialUpdates;
		bool Format16BitsPerPixel;
		uint32 MaxTextureDimension;
		uint32 MaxCubemapDimension;
		uint32 MaxTextureRepeat;
		float MaxAnisotropy;
		uint32 MaxPrimitiveCount;
		uint32 MaxInputSlots;
		uint32 MaxRenderTargets;
		bool OcclusionQueries;
		bool SeparateAlphaBlendPerRenderTarget;
		bool MirrorOnce;
		bool OverlappingVertexElements;
		bool IndependentWriteMasks;
		bool Instancing;
		bool NonPowersof2Unconditionally;
		bool NonPowersof2Conditionally;
	};

	GraphicsCapability FeatureLevelCapabilities[ 7 ] = {
		{ ShaderVersion::Version50, true, true, true, true, true, true, true, true, true, true, true, true, true, true, 64, true, 16, true, true, 16384, 16384, 2048, 16384, 16, 4294967295, 32, 8, true, true, true, true, true, true, false, true, }
		{ ShaderVersion::Version50, true, true, true, true, true, true, true, true, true, true, true, false, false, false, 8, false, 8, false, false, 16384, 16384, 2048, 16384, 16, 4294967295, 32, 8, true, true, true, true, true, true, false, true, }
		{ ShaderVersion::Version41, true, true, false, false, true, true, true, false, true, false, false, false, false, false, 1, false, false, false, false, 8192, 8192, 2048, 8192, 16, 4294967295, 32, 8, true, true, true, true, true, true, false, true, }
		{ ShaderVersion::Version40, true, true, false, false, true, false, true, false, true, false, false, false, false, false, 1, false, false, false, false, 8192, 8192, 2048, 8192, 16, 4294967295, 16, 8, true, true, true, true, true, true, false, true, }
		{ ShaderVersion::Version40d3d93, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, true, false, 4096, 4096, 256, 8192, 16, 1048575, 16, 4, true, true, true, true, true, true, true, false, }
		{ ShaderVersion::Version40d3d91, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, true, false, 2048, 512, 256, 2048, 16, 1048575, 16, 1, true, true, true, true, false, false, true, false, }
		{ ShaderVersion::Version40d3d91, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, true, false, 2048, 512, 256, 128, 2, 65535, 16, 1, false, false, false, false, false, false, true, false, }
	};