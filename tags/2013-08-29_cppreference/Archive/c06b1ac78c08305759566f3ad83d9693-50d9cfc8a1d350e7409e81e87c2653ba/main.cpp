
class ModelMeshPart {
     // At first, having a `MeshPart` seems unncesarry,
     // but as XNA and other non-independent projects
     // have surmised, Parts should be broken up by
     // material, to avoid doing many shader switches
     // thus, a ModelMeshPart contains an
     // Index and/or Vertex Buffer, plus materials related specifically to that buffer
}

class ModelMesh {
    // Here, we put multiple ModelMeshParts
    // We also have bones here, because Bones pertain to a whole Mesh and
    // are not split up by Materials on a single Mesh
    // Thus, this acts as the highlevel "Mesh" that will also
    // take care of animation.
    // Rendering it will just be a matter of making sure the bones match up to the
    // individual mesh parts,
    // but if it gets too complicated we can always just scrap the ModelMeshPart
    // and take the hit for multiple shader constant buffer switches
}

class Model {
    // The high-level container for ModelMesh.
    // It will contain:
    // a ModelTextureCollection, for textures that have been loaded for use with the meshes and materials
    // a ModelBoneCollection, for all the bones in all the meshes
    // a ModelMaterialCollection, for all the materials. This could be moved downstream to ModelMeshPart
    // and we could just make the ModelMeshPart the owner of its own materials (this would eliminate the need for a ModelTextureCollection)
}

int main ( int argc, char* argv[] ) {
    
    
    
}