#shader type vertex
#version 130
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoordinates;

out vec2 v_TextureCoordinates;

uniform mat4 Model;
uniform mat4 Projection;

void main() {
    gl_Position = Projection * Model * a_Position;
    v_TextureCoordinates = a_TextureCoordinates;
}

#shader type fragment
#version 130
#extension GL_ARB_separate_shader_objects : require
out vec4 color;

in vec2 v_TextureCoordinates;

uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture, v_TextureCoordinates);
    color = texColor;
}
