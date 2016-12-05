// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include "glm\gtc\matrix_transform.hpp"
#include "ObjObject.h"
#include "Program.h"
#include "Log.h"
#include "AABB.h"
#include <vector>
#include <memory>

namespace GE
{
	// forward declear, see GameObject.h
	class GameObject;

	enum ComponentType
	{
		kTransform,
		kMeshRenderer,
		kBoxCollider,
		kSphereCollider,
	};

	class Component
	{
	friend class GameObject;

	public:
		Component();
		virtual ~Component();

		virtual void onLoad();
		virtual void onUpdate(float dt);
		virtual void onDraw();
		virtual void onDelete();

	protected:
		GameObject* m_parent;
		ComponentType m_type;
	};

	class Transform : public Component
	{
	public:
		Transform();
		Transform(const Transform& t);
		~Transform();

		inline glm::vec3 getPosition() { return m_position;  }

		inline glm::vec3 getScale() { return m_scale; }

		inline glm::vec3 getRotation() { return m_rotation; }

		inline void setPosition(glm::vec3& p) { m_position = p; }

		inline void setScale(glm::vec3& s) { m_scale = s; }

		inline void setRotation(glm::vec3& r) { m_rotation = r; }

		inline void translate(glm::vec3& p) { m_position += p; }

		glm::mat4 createTransform()
		{
			glm::mat4 m;
			m = glm::scale(m, m_scale);
			m = glm::translate(m, m_position);
			m = glm::rotate(m, m_rotation.x, glm::vec3(1, 0, 0));
			m = glm::rotate(m, m_rotation.y, glm::vec3(0, 1, 0));
			m = glm::rotate(m, m_rotation.z, glm::vec3(0, 0, 1));
			m[3][3] = 1.0f;
			return m;
		}

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
	};

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		void onDraw();

		void MeshRenderer::Draw()
		{
			shared<GEC::ObjObject> mesh(m_mesh);

			if (!mesh->getVertexBuffer()->isIndexed())
			{
				const float* offset = 0;
				glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()->getVBO());
				glBindVertexArray(mesh->getVertexBuffer()->getIBO());
				glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
				glEnableVertexAttribArray(2);
				glDrawArrays(GL_TRIANGLES, 0, mesh->getIndicesCount());
				glDisableVertexAttribArray(2);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(0);
#if _DEBUG
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
#endif
			}
			else
			{
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
			}
		}

		void setTexture(shared<GEC::Texture>& texture) { m_texture = texture; }

		void setMesh(shared<GEC::ObjObject>& mesh) { m_mesh = mesh; }

		void setProgram(shared<GE::Program>& program) { m_shaderProgram = program; }

		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		void setMVPUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P)
		{
			shared<GE::Program> program(m_shaderProgram);
			program->bind();
			program->uniformMatrix4("modelMatrix", 1, M);
			program->uniformMatrix4("viewMatrix", 1, V);
			program->uniformMatrix4("projectionlMatrix", 1, P);
			program->unbind();
		}

	public:
		weak<GEC::Texture> m_texture;
		weak<GEC::ObjObject> m_mesh;
		weak<GE::Program> m_shaderProgram;
		glm::vec2 m_screenRes;
		bool m_usingVertexBuffer;
	};

	class BoxCollider : public Component
	{
	friend class AABB;
	public:
		BoxCollider()
		{
			m_type = kBoxCollider;
			m_boundingBox = GEC::AABB(glm::vec3(0.0f), glm::vec3(1.0f));
			makeVertexBuffer();
			std::string assetPath(ENGINEASSETS);
			GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
			GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
			m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);
		}

		BoxCollider(glm::vec3 center, glm::vec3 size)
		{
			m_type = kBoxCollider;
			m_boundingBox = GEC::AABB(center, size);
			makeVertexBuffer();
			std::string assetPath(ENGINEASSETS);
			GE::Shader vertexShader(std::string(assetPath + "shaders/collisionWireframe.vrt").c_str(), kVertexShader);
			GE::Shader pixelShader(std::string(assetPath + "shaders/collisionWireframe.pix").c_str(), kPixelShader);
			m_shaderProgram = mkShare<GE::Program>(vertexShader, pixelShader);

			
		}

		~BoxCollider();

		void onDraw()
		{
			m_shaderProgram->bind();
			m_shaderProgram->uniform3f("wireframeColour", 128.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f);
			const float* offset = 0;
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer->getVBO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBuffer->getIBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexNormalUV), offset);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 3);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, true, sizeof(vertexNormalUV), offset + 6);
			glEnableVertexAttribArray(2);
			glDrawElements(GL_LINES, (GLsizei)m_indexCount, GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);

			m_shaderProgram->unbind();
		}

		void boundToObject(shared<GEC::ObjObject> obj)
		{
			glm::vec2 X, Y, Z;
			obj->getVertexRange(X, Y, Z);
			m_boundingBox = GEC::AABB(glm::vec3(0.0f), glm::vec3((X.y - X.x), (Y.y - Y.x), (Z.y - Z.x)));
			makeVertexBuffer();
		}

		void setMin(glm::vec3 min) { m_boundingBox.min = min; m_boundingBox.center = ((m_boundingBox.max - m_boundingBox.min) / 2.0f) + m_boundingBox.min; };

		void setMax(glm::vec3 max) { m_boundingBox.max = max; m_boundingBox.center = ((m_boundingBox.max - m_boundingBox.min) / 2.0f) + m_boundingBox.min; };

		inline glm::vec3 getMin() { return m_boundingBox.min; }
							
		inline glm::vec3 getMax() { return m_boundingBox.max; }

		inline glm::vec3 getCenter() { return m_boundingBox.center; }

		bool collision(BoxCollider other)
		{
			return m_boundingBox.intersects(other.m_boundingBox);
		}

		inline void setScreenRes(glm::vec2 screen) { m_screenRes = screen; }

		void setMVPUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P)
		{
			shared<GE::Program> program(m_shaderProgram);
			program->bind();
			program->uniformMatrix4("modelMatrix", 1, M);
			program->uniformMatrix4("viewMatrix", 1, V);
			program->uniformMatrix4("projectionlMatrix", 1, P);
			program->unbind();
		}

		
			void computeBounds(glm::vec3& newPosition)
			{
				m_boundingBox = GEC::AABB(m_boundingBox.center + newPosition, m_boundingBox.size);
			}
		

	public:
		GEC::AABB m_boundingBox;
		glm::vec2 m_screenRes;

	private:

		void makeVertexBuffer()
		{
			std::vector<vertexNormalUV> vertices;
			std::vector<int> indices;

			vertexNormalUV tmp;
			tmp.n = glm::vec3(1.0f);
			tmp.u = glm::vec2(0.0f);
			tmp.v = m_boundingBox.max;
			vertices.push_back(tmp);
			tmp.v = m_boundingBox.max;
			tmp.v.y -= m_boundingBox.size.y;
			vertices.push_back(tmp);
			tmp.v = m_boundingBox.max;
			tmp.v.x -= m_boundingBox.size.x;
			tmp.v.y -= m_boundingBox.size.y;
			vertices.push_back(tmp);
			tmp.v = m_boundingBox.max;
			tmp.v.x -= m_boundingBox.size.x;
			vertices.push_back(tmp);

			tmp.v = m_boundingBox.min;
			vertices.push_back(tmp);
			tmp.v = m_boundingBox.min;
			tmp.v.y += m_boundingBox.size.y;
			vertices.push_back(tmp);
			tmp.v = m_boundingBox.min;
			tmp.v.x += m_boundingBox.size.x;
			tmp.v.y += m_boundingBox.size.y;
			vertices.push_back(tmp);
			tmp.v = m_boundingBox.min;
			tmp.v.x += m_boundingBox.size.x;
			vertices.push_back(tmp);

			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(2);
			indices.push_back(3);
			indices.push_back(3);
			indices.push_back(0);

			indices.push_back(2);
			indices.push_back(4);
			indices.push_back(4);
			indices.push_back(5);
			indices.push_back(5);
			indices.push_back(3);

			indices.push_back(4);
			indices.push_back(7);
			indices.push_back(7);
			indices.push_back(6);
			indices.push_back(6);
			indices.push_back(5);

			indices.push_back(7);
			indices.push_back(1);
			indices.push_back(6);
			indices.push_back(0);

			m_indexCount = indices.size();
			m_vertexBuffer = mkShare<GEC::VertexBuffer>(vertices, indices);
		}

		shared<GEC::VertexBuffer> m_vertexBuffer;
		shared<GE::Program> m_shaderProgram;
		int m_indexCount;
	};
};

