#version 330 core

layout(location = 0) out vec4 color;

in vec3 vertexColor;

uniform vec4 uColor;

void main()
{
	color = vec4(uColor.rgb * vertexColor, uColor.a);
};