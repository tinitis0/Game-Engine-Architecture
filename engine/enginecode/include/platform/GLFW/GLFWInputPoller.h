/*! \file GLFWInputPoller.h */
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \class GLFWInputPoller
	* input poller for getting current keyboard/mouse state specific for the GLFW system
	*/
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed?
		static bool  isMouseButtonPressed(int32_t mouseButton); //!< is the mouse button pressed?
		static glm::vec2 getMousePosition();//!< current mouse position
		static void setCurrentWin(GLFWwindow* newWin) { s_window = newWin; } //!< sets the current window 
	private:
		static GLFWwindow* s_window; //!< Current GLFW window
	};
}



