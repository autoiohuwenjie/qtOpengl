#version 150 core

in vec3 vertexPosition;
in vec2 vertexTexCoord;

out vec3 worldPosition;
out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 mvp;

void main()
{
    // Transform position, normal, and tangent to world coords
    worldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));

    texCoord = vertexTexCoord;

    // Calculate vertex position in clip coordinates
    gl_Position = mvp * vec4(worldPosition, 1.0);
}
