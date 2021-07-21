/*! \file GLFW_OpenGL_Graphics.h*/
#pragma once

#include "core/graphicsContext.h"

namespace Engine
{
	/* \class GLFW_OpenGLGraphics
	* initialise he graphics context for the current window
	*/
	class GLFW_OpenGLGraphics : public GraphicsContext
	{
	public:
		GLFW_OpenGLGraphics(GLFWwindow* win) : m_window(win) {} //!< Constructor
		virtual void init() override; //!< Initialise the graphics context for the given window API
		virtual void swapBuffers() override; //!< Swaps the front and back buffer
	private:
		GLFWwindow* m_window; //!< Pointer to GLFW window
	};
}

