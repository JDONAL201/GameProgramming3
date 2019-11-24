#pragma once
#include "Common.h"
#include "Vertex.h"
#include "ShaderProgram.h"

class Mesh
{
private:

	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;
	GLuint m_vao, m_vbo, m_ebo;

public:

	Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
	void SetUpAttributes(int index, int count, int type, size_t offset);
	void Bind();


	int GetIndiciesCount() { return (int)m_indices.size(); }



};

