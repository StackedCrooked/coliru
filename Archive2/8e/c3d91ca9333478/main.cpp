vs.Source(" \
#version 330\n \
uniform mat4 model; \
uniform mat4 view; \
uniform mat4 perspective; \
in vec3 Position; \
out vec3 cpos; \
void main() { \
    cpos = Position; \
	gl_Position = perspective * view * model * vec4(Position, 1.0); \
}");
vs.Compile();
fs.Source(" \
#version 330\n \
out vec4 fragColor; \
in vec3 cpos; \
void main() { \
	//fragColor = vec4(1.0, 0.0, 0.0, 1.0);  \
	fragColor = vec4(cpos, 1.0); \
}");
