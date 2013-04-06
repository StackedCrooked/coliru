ModelMeshPart Load ( string somefile ) {
    // How access and build ModelMeshPart? :c
}

class ModelMeshPart {
private:
    // How populate with datas? :c
	ModelMesh* parentmodelmesh;
	const Matrix* bonetransforms;
	Matrix world;
	ulword rootbone;
	std::vector<ulword> bones;
	std::unordered_map<String, ulword> boneindices;
	std::vector<ulword> materials;
	std::unordered_map<String, ulword> materialindices;
	BoundingBox box;
	String name;
	ptr<VertexBuffer> vertices;
	ptr<IndexBuffer> indices;
	PrimitiveTopology topology;
	uint32 vertexoffset, indexoffset, primitivecount;

public:
	
	ModelMeshPart ();
    
}

int main ( int argc, char* argv[] ) {
    
    
    
}