// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 06/02/2016
#include "VertexBuffer.h"

namespace GEC
{
	VertexBuffer::VertexBuffer(const std::vector<vertexNormalUV>& vertices, const std::vector<int>& indices)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexNormalUV)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_usingIndexed = true;
	}

	VertexBuffer::VertexBuffer(const std::vector<vertexNormalUV>& vertices)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexNormalUV)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &m_ibo);

		m_usingIndexed = false;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
	}

}; ///< end of namespace