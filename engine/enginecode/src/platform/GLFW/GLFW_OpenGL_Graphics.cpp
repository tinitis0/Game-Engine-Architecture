/*! \file GLFW_OpenGL_Graphics.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "platform/GLFW/GLFW_OpenGL_Graphics.h"
#include "systems/logs.h"

namespace Engine 
{	  
	void GLFW_OpenGLGraphics::init()
	{
		glfwMakeContextCurrent(m_window); //!< make the current window glfw
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); //!< set the result automaticly to load openGL Graphics
		if (!result)
		{
			Logs::error("Could not create OpenGl context for current GLFW window: {0}", result);
		} //!< log error if cant desplay the result
		glEnable(GL_DEBUG_OUTPUT);//!<Enable OpenGl debug output with a callback
		glDebugMessageCallback(
			[](
				GLenum source,
				GLenum type,
				GLenum id,
				GLenum severity,
				GLsizei length,
				const GLchar *message,
				const void *userParam
				)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH :
				Logs::error(message);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				Logs::warn(message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				Logs::info(message);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
			//	Logs::trace(message);
				break;
			}
		}
			, nullptr);
	} //!< debug message call back function

	void GLFW_OpenGLGraphics::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}//!< swap buffers in glfw OpenGL graphics
}