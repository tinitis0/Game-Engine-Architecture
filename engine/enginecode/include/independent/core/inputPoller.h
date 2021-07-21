/*! \file inputPoller.h */
#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	/** \class InputPoller.h 
	* API agnostic input poller for getting current keyboard/mouse state
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed?
		static bool  isMouseButtonPressed(int32_t mouseButton); //!< is the mouse button pressed?
		static glm::vec2 getMousePosition();//!< current mouse position
		static void setNativeWin(void* nativeWin); //!< sets the native window resolution
		inline static float getMouseX() { return getMousePosition().x; } //!< gets the mouse X position
		inline static float getMouseY() { return getMousePosition().y; } //!< gets the mouse Y position




	};
}



