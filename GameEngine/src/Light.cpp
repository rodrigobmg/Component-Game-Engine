/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "Light.h"

namespace GE
{
	Light::Light()
	{
		m_type = kLight;
		m_position = glm::vec3(0, 0, 0);
		m_colour = glm::vec3(1, 1, 1);
		m_intensity = 1.0f;
	}

	Light::~Light()
	{

	}
};