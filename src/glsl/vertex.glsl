#version 460 core

in vec3 vertex;
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec4 inColor;
out vec2 TexCoord;

void main() {
  gl_Position = vec4(position, .5f, 1.0f);
  inColor = gl_Position;
  TexCoord = texCoord;
}
