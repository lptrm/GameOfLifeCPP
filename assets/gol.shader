#shader vertex
#version 330 core

layout(location = 0) in vec4 u_Position;
layout(location = 1) in vec3 u_Color;
layout(location = 2) in vec3 u_Offset;

uniform mat4 u_MVP;

out vec3 fragColor;

void main() {
    vec4 worldPosition = u_MVP * (u_Position + vec4(u_Offset, 1.0));
    gl_Position = worldPosition;

    fragColor = u_Color;
}

#shader fragment
#version 330 core

in vec3 fragColor;
out vec4 fragOutput;

void main() {
    fragOutput = vec4(fragColor, 1.0);
}
