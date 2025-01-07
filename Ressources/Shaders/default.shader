#VERTEX SHADER
#version 330 core

layout (location = 0) in vec3 pos;
uniform mat4 mvp;

out vec3 vertex_color;

void main() {
	gl_Position = mvp * vec4(pos, 1.0f);

	vertex_color = (pos + vec3(1.0f)) / 2.0f;
}


#FRAGMENT SHADER
#version 330 core

in vec3 vertex_color;

out vec4 frag_color;

void main() {
	frag_color = vec4(vertex_color, 1.0f);
}
