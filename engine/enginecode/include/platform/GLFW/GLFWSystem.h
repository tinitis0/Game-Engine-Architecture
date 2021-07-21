/*! \file GLFWSystem.h
*/
#pragma once

#include "systems/system.h"
#include "systems/logs.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWSystem
	* starts the GLFW system. gets the error, displays the message and terminates the GLFW system
	*/
	class GLFWSystem : public System
	{
		virtual void start(SystemSignal init = SystemSignal::None, ...) override
		{
			auto errorCode = glfwInit();
			if (!errorCode)
			{
				Logs::error("Cannot init GLFW: {0}", errorCode); //!< logs the error
			}
		} //!< Start the system

		virtual void stop(SystemSignal close = SystemSignal::None, ...) override
		{
			glfwTerminate();
		} //!< Stop the system
	};
}
