// Shaders/glsl/triangule.vert
#version 450 core

// Data comes from VBO (position and color)
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_color;

// Pass the color to the fragment shader
layout(location = 0) out vec4 v_color;

// Object transformation — updated by draw call
layout(push_constant) uniform PushConstants {
	mat4 u_model;
} Push;

void main() {
    v_color = a_color;
	gl_Position = Push.u_transform * vec4(a_Position, 1.0);
}