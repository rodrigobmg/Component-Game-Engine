/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include "Shaders.h"
#include "glm/common.hpp"
#include "glm/glm.hpp"

namespace GE
{
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  The different types of buffers
	//----------------------------------------------------------------------------------------------------------------------
	enum bufferTypes
	{
		kArrayBuffer = GL_ARRAY_BUFFER,
		kArrayElementBuffer = GL_ELEMENT_ARRAY_BUFFER,
		kTextureBuffer = GL_TEXTURE_BUFFER,
		kAtomicBuffer = GL_ATOMIC_COUNTER_BUFFER,
		kCopyReadBuffer = GL_COPY_READ_BUFFER,
		kCopyWriteBuffer = GL_COPY_WRITE_BUFFER,
		kDispatchIndirectBuffer = GL_DISPATCH_INDIRECT_BUFFER,
		kDrawIndriectBuffer = GL_DRAW_INDIRECT_BUFFER,
		kPackPixelBuffer = GL_PIXEL_PACK_BUFFER,
		kUnpackPixelBuffer = GL_PIXEL_UNPACK_BUFFER,
		kQueryBuffer = GL_QUERY_BUFFER,
		kShaderStoreBuffer = GL_SHADER_STORAGE_BUFFER,
		kFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
		kUniformBuffer = GL_UNIFORM_BUFFER
	};

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  The different types of buffer usage
	//----------------------------------------------------------------------------------------------------------------------
	enum bufferUsage
	{
		kStreamD = GL_STREAM_DRAW,
		kStreamR = GL_STREAM_READ,
		kStreamC = GL_STREAM_COPY,
		kStaticD = GL_STATIC_DRAW,
		kStaticR = GL_STATIC_READ,
		kStaticC = GL_STATIC_COPY,
		kDynamicD = GL_DYNAMIC_DRAW,
		kDynamicR = GL_DYNAMIC_READ,
		kDynamicC = GL_DYNAMIC_COPY
	};


	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  a shader program
	//----------------------------------------------------------------------------------------------------------------------
	class Program
	{
	public:

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  constructor creates empty program
		//----------------------------------------------------------------------------------------------------------------------
		Program();
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  constructor creates program with two attached shader (i.e. vertex/fragment)
		/// prama		GE::Shader vertex shader
		/// prama		GE::Shader fragment shader
		//----------------------------------------------------------------------------------------------------------------------
		Program(Shader& shaderOne, Shader& shaderTwo);

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  destructor
		//----------------------------------------------------------------------------------------------------------------------
		~Program();

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  binds this program in OpenGL
		//----------------------------------------------------------------------------------------------------------------------
		inline void bind()
		{ glUseProgram(m_program); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  unbinds this program in OpenGL
		//----------------------------------------------------------------------------------------------------------------------
		inline void unbind()
		{ glUseProgram(0); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  get the shader ID
		/// \return uint32_t
		//----------------------------------------------------------------------------------------------------------------------
		inline uint32_t getProgram()
		{ return m_program; }

		// float
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		float 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform1f(const char* uniformName, const float& a)
		{ glUniform1f(glGetUniformLocation(m_program, uniformName), a); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		float 
		/// prama		float 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2f(const char* uniformName, const float& a, const float& b)
		{ glUniform2f(glGetUniformLocation(m_program, uniformName), a, b); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		float 
		/// prama		float 
		/// prama		float 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3f(const char* uniformName, const float& a, const float& b, const float& c)
		{ glUniform3f(glGetUniformLocation(m_program, uniformName), a, b, c); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		float 
		/// prama		float 
		/// prama		float 
		/// prama		float 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4f(const char* uniformName, const float& a, const float& b, const float& c, const float& d)
		{ glUniform4f(glGetUniformLocation(m_program, uniformName), a, b, c, d); }
		


		// float using glm::Vec2/3
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		glm::vec2 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2f(const char* uniformName, const glm::vec2& v)
		{ glUniform2f(glGetUniformLocation(m_program, uniformName), v.x, v.y); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		glm::vec3 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3f(const char* uniformName, const glm::vec3& v)
		{ glUniform3f(glGetUniformLocation(m_program, uniformName), v.x, v.y, v.z); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		glm::vec4 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4f(const char* uniformName, const glm::vec4& v)
		{ glUniform4f(glGetUniformLocation(m_program, uniformName), v.x, v.y, v.z, v.z); }



		// int
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a int shader uniform
		/// prama		char* uniform name
		/// prama		int 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform1i(const char* uniformName, const int& a)
		{ glUniform1i(glGetUniformLocation(m_program, uniformName), a);	}
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a int shader uniform
		/// prama		char* uniform name
		/// prama		int 
		/// prama		int 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2i(const char* uniformName, const int& a, const int& b)
		{ glUniform2i(glGetUniformLocation(m_program, uniformName), a, b); }
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a int shader uniform
		/// prama		char* uniform name
		/// prama		int 
		/// prama		int 
		/// prama		int 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3i(const char* uniformName, const int& a, const int& b, const int& c)
		{ glUniform3i(glGetUniformLocation(m_program, uniformName), a, b, c); }
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a float shader uniform
		/// prama		char* uniform name
		/// prama		int 
		/// prama		int 
		/// prama		int 
		/// prama		int 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4i(const char* uniformName, const int& a, const int& b, const int& c, const int& d)
		{ glUniform4i(glGetUniformLocation(m_program, uniformName), a, b, c, d); }



		// unsigned int
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		uint32_t 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform1ui(const char* uniformName, const uint32_t& a)
		{ glUniform1ui(glGetUniformLocation(m_program, uniformName), a); }
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		uint32_t 
		/// prama		uint32_t 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2ui(const char* uniformName, const uint32_t& a, const uint32_t& b)
		{ glUniform2ui(glGetUniformLocation(m_program, uniformName), a, b); }
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		uint32_t 
		/// prama		uint32_t 
		/// prama		uint32_t 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3ui(const char* uniformName, const uint32_t& a, const uint32_t& b, const uint32_t& c)
		{ glUniform3ui(glGetUniformLocation(m_program, uniformName), a, b, c); }
		
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		uint32_t 
		/// prama		uint32_t 
		/// prama		uint32_t 
		/// prama		uint32_t 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4ui(const char* uniformName, const uint32_t& a, const uint32_t& b, const uint32_t& c, const uint32_t& d)
		{ glUniform4ui(glGetUniformLocation(m_program, uniformName), a, b, c, d); }



		// modify float
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a float shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform1fv(const char* uniformName, const int32_t& count, const float* value)
		{ glUniform1fv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a float shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2fv(const char* uniformName, const int32_t& count, const float* value)
		{ glUniform2fv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a float shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3fv(const char* uniformName, const int32_t& count, const float* value)
		{ glUniform3fv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a float shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4fv(const char* uniformName, const int32_t& count, const float* value)
		{ glUniform4fv(glGetUniformLocation(m_program, uniformName), count, value); }


		// modify int
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		int* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform1iv(const char* uniformName, const int32_t& count, const int* value)
		{ glUniform1iv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		int* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2iv(const char* uniformName, const int32_t& count, const int* value)
		{ glUniform2iv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		int* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3iv(const char* uniformName, const int32_t& count, const int* value)
		{ glUniform3iv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		int* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4iv(const char* uniformName, const int32_t& count, const int* value)
		{ glUniform4iv(glGetUniformLocation(m_program, uniformName), count, value); }


		// modify unsigned int
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		uint32_t* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform1uiv(const char* uniformName, const  int32_t& count, const uint32_t* value)
		{ glUniform1uiv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		uint32_t* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform2uiv(const char* uniformName, const int32_t& count, const uint32_t* value)
		{ glUniform2uiv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		uint32_t* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform3uiv(const char* uniformName, const int32_t& count, const uint32_t* value)
		{ glUniform3uiv(glGetUniformLocation(m_program, uniformName), count, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a unsigned int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		uint32_t* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniform4uiv(const char* uniformName, const int32_t& count, const uint32_t* value)
		{ glUniform4uiv(glGetUniformLocation(m_program, uniformName), count, value); }


		// matrix
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float*
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix2(const char* uniformName, const int32_t& count, const float* value)
		{ glUniformMatrix2fv(glGetUniformLocation(m_program, uniformName), count, false, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		bool  transpose
		/// prama		float*
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix2(const char* uniformName, const int32_t& count, bool& transpose, const float* value)
		{ glUniformMatrix2fv(glGetUniformLocation(m_program, uniformName), count, transpose, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float*
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix3(const char* uniformName, const int32_t& count, const float* value)
		{ glUniformMatrix3fv(glGetUniformLocation(m_program, uniformName), count, false, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		bool  transpose
		/// prama		float* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix3(const char* uniformName, const int32_t& count, bool& transpose, const float* value)
		{ glUniformMatrix3fv(glGetUniformLocation(m_program, uniformName), count, transpose, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		float* 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix4(const char* uniformName, const int32_t& count, const float* value)
		{ glUniformMatrix4fv(glGetUniformLocation(m_program, uniformName), count, false, value); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		bool  transpose
		/// prama		float*
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix4(const char* uniformName, const int32_t& count, bool& transpose, const float* value)
		{ glUniformMatrix4fv(glGetUniformLocation(m_program, uniformName), count, transpose, value); }


		// float using math::Mat3/4
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  set a matrix shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		glm::mat3x3 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix3(const char* uniformName, const int32_t& count, const glm::mat3x3& m)
		{ glUniformMatrix3fv(glGetUniformLocation(m_program, uniformName), count, false, &m[0][0]); }

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief  modify a int shader uniform
		/// prama		char* uniform name
		/// prama		int32_t 
		/// prama		glm::mat4x4 
		//----------------------------------------------------------------------------------------------------------------------
		inline void uniformMatrix4(const char* uniformName, const int32_t& count, const glm::mat4x4& m)
		{ glUniformMatrix4fv(glGetUniformLocation(m_program, uniformName), count, false, &m[0][0]); }

	private:
		uint32_t m_program; ///< shader location 
	};

}; /// end of namespace
