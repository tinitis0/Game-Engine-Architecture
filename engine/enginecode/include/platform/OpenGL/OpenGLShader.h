/*! \file OpenGLShader.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include "rendering/shaders.h"

namespace Engine 
{
	/** \class OpenGLShader
	* Creates a shader program
	*/
	class OpenGLShader : public Shaders
	{
	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath); //!< Constructor takes multiple files
		OpenGLShader(const char* filepath); //!< Constructor only takes single file
		virtual ~OpenGLShader(); //!< Deconstructor
		virtual inline uint32_t getID() const { return m_OpenGL_ID; } //!< Gets the int ID and returns render ID
		virtual void uploadInt(const char* name, int value) override; //!< upload sample2D
		virtual void uploadFloat(const char* name, float value)override; //!< upload Float
		virtual void uploadFloat2(const char* name, const glm::vec2& value)override; //!< upload Float2
		virtual void uploadFloat3(const char* name, const glm::vec3& value)override; //!< upload Float3
		virtual void uploadFloat4(const char* name, const glm::vec4& value)override; //!< upload Float4
		virtual void uploadMat4(const char* name, const glm::mat4& value)override; //!< upload matricies

	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		void compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc); //!< compiles and links shaders
	};
}