#version 330 core
layout(location = 0) in vec3 aPos;
out vec3 vertexColor; // Output color to fragment shader
uniform vec3 triangleColor; // Uniform variable for triangle color
void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = triangleColor; // Pass the triangle color to the fragment shader
}