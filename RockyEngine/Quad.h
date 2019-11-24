#pragma once
#include "pch.h"
#include "Vertex.h"
namespace Quad
{
	std::vector <Vertex> quadVertices
	{
		Vertex(glm::vec3(0.5 , 0.5f , 0.f)), //topRight
		Vertex(glm::vec3(0.5f , -0.5f , 0.f)), //bottomRight
		Vertex(glm::vec3(-0.5f , -0.5f , 0)), //bottomLeft
		Vertex(glm::vec3(-0.5f , 0.5f , 0)) //topLeft
	};
	std::vector < int > quadIndices
	{
		0 , 1 , 3 ,
		1 , 2 , 3
	};
}