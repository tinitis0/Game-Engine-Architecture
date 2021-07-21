/*! \file OpenGLShader.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLShader.h"
#include <fstream>
#include"systems/logs.h"
#include <string>
#include <array>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	OpenGLShader::OpenGLShader(const char * vertexFilepath, const char * fragmentFilepath)
	{
		std::string line, vertexSource, fragmentSource; 
		std::fstream handle(vertexFilepath, std::ios::in); //!< open the file

		if (handle.is_open()) 
		{			
			while (getline(handle, line)) 
			{
				vertexSource += line + "\n";
			} //!< read it in line by line 
		} //!< if its open
		else 
		{
			Logs::error("Could not open vertex shader source: {0}", vertexFilepath); //!< log an error and return
			return;
		} //!< if not
		handle.close(); //!< close the handle

		handle.open(fragmentFilepath, std::ios::in); //!< open the file
		if (handle.is_open()) 
		{
			while (getline(handle, line)) 
			{
				fragmentSource += line + "\n";
			}//!< read it in line by line 
		}//!< if its open
		else 
		{
			Logs::error("Could not open fragment shader source: {0}", fragmentFilepath); //!< log an error and return
			return;
		} //!< if not
		handle.close(); //!< close the handle
		compileAndLink(vertexSource.c_str(), fragmentSource.c_str()); //!< compile and link shaders
	}

	OpenGLShader::OpenGLShader(const char * filepath)
	{
		enum Region {None = -1, Vertex = 0, Fragment, Geometry, TessallationControl, TesselationEvaluation, Compute }; //!< enum regions
		std::string line;
		std::array<std::string, Region::Compute + 1> source; 
	 	uint32_t region = Region::None;//!< default region to none

		std::fstream handle(filepath, std::ios::in); //!< open the file
		if (handle.is_open()) 
		{			
			while (getline(handle, line)) 
			{
				
				if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; continue;} //!< finds the region
				if (line.find("#region Fragment") != std::string::npos) {region = Region::Fragment; continue;} //!< finds the region
				if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry; continue; } //!< finds the region
				if (line.find("#region TessallationControl") != std::string::npos) { region = Region::TessallationControl; continue;} //!< finds the region
				if (line.find("#region TesselationEvaluation") != std::string::npos) { region = Region::TesselationEvaluation; continue;} //!< finds the region
				if (line.find("#region Compute") != std::string::npos) {region = Region::Compute; continue;} //!< finds the region
				if(region != Region::None) source[region] += (line + "\n"); //!< if there is no region
			}//!< read it in line by line 
		}//!< if its open
		else 
		{
			Logs::error("Could not open vertex shader source: {0}", filepath); //!< log an error and return
			return;
		}//!< if not
		handle.close(); //!< close the handle
		compileAndLink(source[Region::Vertex].c_str(), source[Region::Fragment].c_str()); //!< compile and link shaders
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_OpenGL_ID);
	}//!< deconstructor

	void OpenGLShader::uploadInt(const char * name, int value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1i(location, value);
	} //!< upload int

	void OpenGLShader::uploadFloat(const char * name, float value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1f(location, value);
	} //!< upload float

	void OpenGLShader::uploadFloat2(const char * name, const glm::vec2 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform2f(location, value.x, value.y);
	} //!< upload float2

	void OpenGLShader::uploadFloat3(const char * name, const glm::vec3 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform3f(location, value.x, value.y, value.z);
	} //!< upload float3

	void OpenGLShader::uploadFloat4(const char * name, const glm::vec4 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	} //!< upload float4

	void OpenGLShader::uploadMat4(const char * name, const glm::mat4 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}//!< upload mat4

	void OpenGLShader::compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //!<set vertex shader to fl vertex shader

		const GLchar* source = vertexShaderSrc; //!< get the source
		glShaderSource(vertexShader, 1, &source, 0); //!< shader source
		glCompileShader(vertexShader); //!< compile the shader

		GLint isCompiled = 0; //!< is compiled set to 0 by default
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled); //!< get shader IV
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0; //!< max Lenght set to 0 by default
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength); //!< get shader IV

			std::vector<GLchar> infoLog(maxLength); //!< info log max lenght 
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]); //!< get shader info logger
			Logs::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< log the error

			glDeleteShader(vertexShader); //!< delete shader
			return;
		} //!< if not complied 

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //!< create shader from fragment shader  
		source = fragmentShaderSrc; //!< shader source
		glShaderSource(fragmentShader, 1, &source, 0); //!< shader source
		glCompileShader(fragmentShader); //!< compile shader
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);//!< get shader IV
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0; //!< set the maxLength to 0
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength); //!< get shader IV
			std::vector<GLchar> infoLog(maxLength);//!< get data from max Lenght
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);//!< get logger info
			Logs::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< log the error
			glDeleteShader(fragmentShader); //!< delete the fragment shader
			glDeleteShader(vertexShader); //!< delete the vertex shader
			return;
		}//!< is not compiled

		m_OpenGL_ID = glCreateProgram(); //!< create program using OpenGL ID
		glAttachShader(m_OpenGL_ID, vertexShader); //!< attach vertex shader and OpenGL ID
		glAttachShader(m_OpenGL_ID, fragmentShader); //!< attach fragment shader and OpenGL ID
		glLinkProgram(m_OpenGL_ID); //!< link OpenGL ID
		GLint isLinked = 0; //!< is linked set to 0
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked); //!< get program IV
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength); //!< get program IV
			std::vector<GLchar> infoLog(maxLength); 
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]); //!< get log info
			Logs::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end())); //!< Log error
			glDeleteProgram(m_OpenGL_ID); //!< delete OpenGL ID
			glDeleteShader(vertexShader);  //!< delete the vertex shader
			glDeleteShader(fragmentShader); //!< delete the fragment shader
			return;
		} //!< is not linked

		glDetachShader(m_OpenGL_ID, vertexShader); //!< deatach vertex shader
		glDetachShader(m_OpenGL_ID, fragmentShader); //!< deatach fragment shader
	}
}