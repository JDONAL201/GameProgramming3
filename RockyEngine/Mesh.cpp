#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	m_indices = indices;
	m_vertices = vertices;

	//Generate and bind the vertex array object so it can keep the current vertex buffer object and attributes

	GL_ATTEMPT(glGenVertexArrays(1, &m_vao)); //Generate vertex array object 
	GL_ATTEMPT(glBindVertexArray(m_vao));
	
	GL_ATTEMPT(glGenBuffers(1, &m_vbo));
	GL_ATTEMPT(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GL_ATTEMPT(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &vertices[0], GL_STATIC_DRAW));
	
	
	GL_ATTEMPT(glGenBuffers(1, &m_ebo));
	GL_ATTEMPT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
	GL_ATTEMPT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), &indices[0], GL_STATIC_DRAW));
	
	//Set the IDs for the positions, color, uv and normals
	SetUpAttributes(0, 3, GL_FLOAT, 0); //pos

	SetUpAttributes(1, 4, GL_FLOAT, sizeof(glm::vec3)); // takes in ID , the data type and how much of to skip  / color

	SetUpAttributes(2, 2, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4)); //uv

	SetUpAttributes(3, 3, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2)); // normal

	//SetUpAttributes(4, 3, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2)+ sizeof(glm::vec3)); // normal


	//SetUpAttributes(5, 3, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2) + sizeof(glm::vec3)+ sizeof(glm::vec3)); // normal

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GL_ATTEMPT(glBindVertexArray(0));
}

void Mesh::SetUpAttributes(int index, int count, int type, size_t offset)
{
	GL_ATTEMPT(glVertexAttribPointer(index, count, type, GL_FALSE, sizeof(Vertex), (void**)offset));
	GL_ATTEMPT(glEnableVertexAttribArray(index));
}

void Mesh::Bind()
{
	GL_ATTEMPT(glBindVertexArray(m_vao));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
