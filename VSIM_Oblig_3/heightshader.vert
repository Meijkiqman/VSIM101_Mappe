#version 330 core
layout (location = 0) in vec3 aPos;

out float Height;
out vec3 Position;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main()
{
    Height = aPos.y;
    Position = (vMatrix *  mMatrix * vec4(aPos, 1.0)).xyz;
    gl_Position = pMatrix * vMatrix * mMatrix *  vec4(aPos, 1.0);
}
