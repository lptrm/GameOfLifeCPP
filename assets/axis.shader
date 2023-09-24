#shader vertex
#version 330 core
layout(location = 0) in vec3 inPosition;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(inPosition, 1.0);
}
#shader fragment
#version 330 core
out vec4 FragColor;
uniform vec3 u_Color;

void main()
{
    FragColor = vec4(u_Color, 1.0);
}
