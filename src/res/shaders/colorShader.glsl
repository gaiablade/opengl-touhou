#shader type vertex
#version 130
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoordinates;

uniform mat4 Model;
uniform mat4 Projection;

void main() {
    gl_Position = Projection * Model * a_Position;
}

#shader type fragment
#version 130
#extension GL_ARB_separate_shader_objects : require
out vec4 color;

uniform vec4 u_Color;

void main() {
    //color = u_Color;
    color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
