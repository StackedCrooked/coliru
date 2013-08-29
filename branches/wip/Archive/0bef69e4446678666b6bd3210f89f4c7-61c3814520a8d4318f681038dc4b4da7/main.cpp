void init_draw_data() {
    /* works
	auto shaders = new std::vector<Jellyot::Shader>();
	shaders->emplace_back(Jellyot::ShaderType::Vertex, strVertexShader);
	shaders->emplace_back(Jellyot::ShaderType::Fragment, strFragmentShader);
	*/
	// Doesn't
	auto shaders = std::vector<Jellyot::Shader>();
	shaders.emplace_back(Jellyot::ShaderType::Vertex, strVertexShader);
	shaders.emplace_back(Jellyot::ShaderType::Fragment, strFragmentShader);
	
	myproggy = new Jellyot::Program(shaders.begin(), shaders.end());
	theProgram = myproggy->GetHandle();

	glGenBuffers(1, &positionBufferObject); //Construct the buffer

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject); //Set buffer pointer to positionBufferObject
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW); //Set data
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Set buffer pointer to null <<--- this is line 55
}