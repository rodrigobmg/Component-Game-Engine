// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#include "Components.h"

namespace GE
{
	Component::Component()
	{

	}

	Component::~Component()
	{

	}

	void Component::onLoad()
	{

	}

	void Component::onUpdate(float dt)
	{

	}

	void Component::onDraw()
	{

	}

	void Component::onDelete()
	{
		//m_parent.reset();
		m_parent = nullptr;
	}

	Transform::Transform()
	{
		m_type = kTransform;
		m_position = glm::vec3(0.0f);
		m_scale = glm::vec3(1.0f);
		m_rotation = glm::vec3(0.0f);
	}

	Transform::Transform(const Transform & t)
	{
		m_position = t.m_position;
		m_scale = t.m_scale;
		m_rotation = t.m_rotation;
	}

	Transform::~Transform()
	{

	}

	MeshRenderer::MeshRenderer()
	{
		m_type = kMeshRenderer;
	}

	MeshRenderer::MeshRenderer(const MeshRenderer & m)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::onDraw()
	{
		glm::mat4 model(8.0f);
		model[3][3] = 1.0f;
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 5.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::perspective(45.0f, m_screenRes.x / m_screenRes.y, 0.1f, 100.0f);

		shared<GE::Program> program(m_shaderProgram);
		shared<GEC::ObjObject> mesh(m_mesh);
		shared<GEC::Texture> texture(m_texture);
		program->bind();
		texture->bind(1);
		program->uniform1i("texture", 1);
		//program->uniformMatrix4("modelMatrix", 1, model);
		//program->uniformMatrix4("viewMatrix", 1, view);
		//program->uniformMatrix4("projectionlMatrix", 1, projection);

		const float* offset = 0;
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()->getVBO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getVertexBuffer()->getIBO());
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
		glEnableVertexAttribArray(2);
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
#if _DEBUG
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif

		texture->unbind();
		program->unbind();
	}
};
