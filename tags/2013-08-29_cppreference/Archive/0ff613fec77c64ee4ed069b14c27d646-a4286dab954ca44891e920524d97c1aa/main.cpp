Uniform& operator[](std:string name) {
    auto found = uniforms.find(name);
	if(found == uniforms.end()) {
		found.insert(Uniform(*this, name);
		return uniforms.find(name)
	} else {
		return *found;
	}
}