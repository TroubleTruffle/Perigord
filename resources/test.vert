#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Color;

out vec3 vertexColor;

uniform vec3 u_Position;

void main()
{
	vertexColor = Color;
	gl_Position.xyz = position - u_Position;
	gl_Position.w = 1;
};