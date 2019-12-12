#pragma once
#include "pch.h"
#include "Vertex.h"
namespace Shapes
{
	std::vector<Vertex> cubeVertices
	{
			Vertex(glm::vec3(-1.f , 1.f , -1.f) , glm::vec4(0), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(-1.f,-1.f ,-1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(1.f,1.f,-1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(1.f,-1.f,-1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(-1.f,1.f,1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(1.f,1.f,1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(-1.f,-1.f,1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),
			Vertex(glm::vec3(1.f,-1.f,1.f), glm::vec4(0.f), glm::vec2(0.f,0.f)),


	};

	std::vector<unsigned int> cubeIndices
	{
		0, 1, 2,// front
		2, 1, 3,

		2, 3, 5,// right
		5, 3, 7,

		5, 7, 4,// back
		4, 7, 6,

		4, 6, 0,// left
		0, 6, 1,

		4, 0, 5,// top
		5, 0, 2,

		1, 6, 3,// bottom
		3, 6, 7
	};


	//std::vector <Vertex> quadVertices
	//{
	//Vertex(glm::vec3(0.5 , 0.5f , 0.f)), //topRight
	//Vertex(glm::vec3(0.5f , -0.5f , 0.f)), //bottomRight
	//Vertex(glm::vec3(-0.5f , -0.5f , 0)), //bottomLeft
	//Vertex(glm::vec3(-0.5f , 0.5f , 0)) //topLeft
	//};
	//std::vector < int > quadIndices
	//{
	//0 , 1 , 3 ,
	//1 , 2 , 3
	//};
}