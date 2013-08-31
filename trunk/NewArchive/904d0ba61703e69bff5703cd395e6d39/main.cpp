template <typename T>
    class CommonShaderMethod : GraphicsResource {
		static_assert( std::is_same<T, ID3D11VertexShader>::value || 
			std::is_same<T, ID3D11VertexShader>::value || 
			std::is_same<T, ID3D11GeometryShader>::value || 
			std::is_same<T, ID3D11HullShader>::value || 
			std::is_same<T, ID3D11DomainShader>::value || 
			std::is_same<T, ID3D11VertexShader>::value, 
			"Type must be one of the ID3D*Shader Types")
		D3D11_SHADER_DESC ShaderDescription;
		ShaderMethodDescription MethodDescription;
		ubiquitous_ptr<ID3D11ShaderReflection, ReleaseDirectX> Reflection;	
		ubiquitous_ptr<ID3DBlob, ReleaseDirectX> Bytecode;
		ubiquitous_ptr<ID3DBlob, ReleaseDirectX> Errors;
		ubiquitous_ptr<T, ReleaseDirectX> Shader;
		ubiquitous_ptr<VertexDeclaration> Declaration;


	};