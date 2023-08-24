#shader vertex
#version 330 core
layout(location = 0) in vec2 inPosition;
out vec2 fragTexCoord;

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);
    fragTexCoord = inPosition * 0.5 + 0.5;
}

#shader fragment
#version 330 core
uniform sampler2D gameGrid;
in vec2 fragTexCoord;
out vec4 outColor;

void main() {
    vec2 texCoord = fragTexCoord;
    
    float cellValue = texture(gameGrid, texCoord).r;

    outColor = vec4(cellValue, cellValue, cellValue, 1.0);
}
