//==================================== Vertex
#version 330
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
in vec3 Position;
out vec3 newPosition;
void main() {
    newPosition = Position;
	gl_Position = perspective * view * model * vec4(Position, 1.0);
}

//==================================== Fragment
#version 330
in vec3 newPosition;
out vec4 fragColor;
void main() {
	//fragColor = vec4(1.0, 0.0, 0.0, 1.0);
	fragColor = vec4(newPosition, 1.0);
}