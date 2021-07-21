/*! \file GLFWInputPoller.cpp */

#include "engine_pch.h"
#include "platform/GLFW/GLFWInputPoller.h"

namespace Engine
{
	GLFWwindow* GLFWInputPoller::s_window = nullptr; //!< set window pointer to null pointer

	bool GLFWInputPoller::isKeyPressed(int32_t keyCode) 
	{
		if (s_window)
		{
			auto answer = glfwGetKey(s_window, keyCode);
			return answer == GLFW_PRESS ||  answer ==GLFW_REPEAT;
		}
		return false; 
	} //!< is key pressed?

	bool GLFWInputPoller::isMouseButtonPressed(int32_t mouseButton) 
	{
		if (s_window)
		{
			auto answer = glfwGetMouseButton(s_window, mouseButton);
			return answer == GLFW_PRESS;
		}
		return false;
	} //!< is mouse button pressed?

	glm::vec2 GLFWInputPoller::getMousePosition() 
	{
		if (s_window)
		{
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));
		}
		return { -1.f,1.f };
	} //!< mouse position
}