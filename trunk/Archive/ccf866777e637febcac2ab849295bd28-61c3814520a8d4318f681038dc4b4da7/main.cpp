void test() {
    Jellyot::Shader a(Jellyot::ShaderType::Vertex, strVertexShader); // Destorys fine
	Jellyot::Shader b(Jellyot::ShaderType::Vertex, strVertexShader); // Sigsegv
	Jellyot::Shader c(Jellyot::ShaderType::Vertex, strVertexShader);
	Jellyot::Shader d(Jellyot::ShaderType::Vertex, strVertexShader);
}