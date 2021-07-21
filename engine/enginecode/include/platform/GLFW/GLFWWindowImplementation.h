/*! \file GLFWWindowImplementation.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \class GLFWWindowImplementation 
	* Implemetntation of window using GLFW	
	*/
	class GLFWWindowImplementation : public Window
	{
	public:
		GLFWWindowImplementation(const WindowProperties& properties); //!< Constructor
		virtual void init(const WindowProperties& properties)  override; //!< initilising routine 
		virtual void close() override; //!< close the window 	
		//virtual ~Window() {}; //!<virtual constructor
		virtual void onUpdate(float timestep) override; //!< on update function
		virtual void setVSync(bool vSync) override; //!< gets the refresh rate
		virtual inline unsigned int getWidth() const override { return m_props.m_width; } //!< width of window
		virtual inline unsigned int getHeight() const override { return m_props.m_height; }//!< height of window
		virtual inline void* getNativeWindow() const override { return  m_native; } //!< gets the underlying platform
		virtual inline bool isFullScreenMode() const override {return m_props.m_isFullScreen; }//!< fullscreen mode
		virtual inline bool isVSync() const override {return m_props.m_isVSync; }//!< vSync

	private:
		WindowProperties m_props; //!< Properties
		GLFWwindow * m_native; //!< native GLFW Window
		float m_aspectRatio; //!< Aspect ratio 
		GLFWmonitor* primary = glfwGetPrimaryMonitor(); //!< gets the primary monitor
	};

}
