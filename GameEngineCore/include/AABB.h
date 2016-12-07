// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 08/11/2016
#pragma once
#include <cmath>
#include "glm\vec3.hpp"

namespace GEC
{
	class AABB
	{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		//----------------------------------------------------------------------------------------------------------------------
		AABB() : center(0.0f), size(1.0f), extents(size * 0.5f), min(center - extents), max(center + extents)
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);
		}

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Constructor
		/// prama		glm::vec3 center
		/// prama		glm::vec3 size
		//----------------------------------------------------------------------------------------------------------------------
		AABB(glm::vec3 center, glm::vec3 size) : center(center), size(size), extents(size * 0.5f) 
		{
			min = glm::vec3(center - extents);
			max = glm::vec3(center + extents);
		}
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  Desstructor
		//----------------------------------------------------------------------------------------------------------------------
		~AABB() { };

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  is a point inside this AABB
		/// prama		glm::vec3 point
		/// \return	bool
		//----------------------------------------------------------------------------------------------------------------------
		bool contains(glm::vec3 point);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  does this AABB intersect another AABB
		/// prama		glm::vec3 point
		/// \return	bool
		//----------------------------------------------------------------------------------------------------------------------
		bool intersects(const AABB& const aabb);

	public:
		glm::vec3 min;
		glm::vec3 max;
		glm::vec3 center;
		glm::vec3 size;
		glm::vec3 extents;
	};
};
