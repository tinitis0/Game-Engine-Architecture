/*! \file inputPoller.cpp */

#include "engine_pch.h"
#include "core/inputPoller.h"
#ifdef NG_PLATFORM_WINDOWS
#include"platform/GLFW/GLFWInputPoller.h"
#endif 

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS

	bool InputPoller::isKeyPressed(int32_t keyCode)
	{
		return GLFWInputPoller::isKeyPressed(keyCode);
	} //!< is the key pressed

	bool InputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		return GLFWInputPoller::isMouseButtonPressed(mouseButton);
	} //!< is the mouse button pressed

	glm::vec2 InputPoller::getMousePosition()
	{
		return GLFWInputPoller::getMousePosition();
	} //!< gets the mouse position

	void InputPoller::setNativeWin(void * nativeWin)
	{
		GLFWInputPoller::setCurrentWin(reinterpret_cast<GLFWwindow*>(nativeWin));
	} //!<  sets the native window resolution

#endif 
}
