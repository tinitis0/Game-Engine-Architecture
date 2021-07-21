/*! \file GLFWWindowImplementation.cpp */

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImplementation.h"
#include "platform/GLFW/GLFW_OpenGL_Graphics.h"
#include "systems/logs.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImplementation(properties);
	}//!< create window with properties
#endif NG_PLATFORM_WINDOWS

	GLFWWindowImplementation::GLFWWindowImplementation(const WindowProperties & properties) //!< Constructor
	{
		init(properties);
	} //!< implement window

	void GLFWWindowImplementation::init(const WindowProperties & properties) 
	{
		m_props = properties; //!< sets properties
		m_aspectRatio = static_cast<float> (m_props.m_width) / static_cast<float> (m_props.m_height); //!< gets aspect ration of the monitor
		if (m_props.m_isFullScreen)
		{
			Logs::error("Fullscreen not yet implemented");
			m_native = glfwCreateWindow(1080, 920, "Title", glfwGetPrimaryMonitor(), NULL);
		}//!< sets the window with set parameters
		else
		{
			m_native = glfwCreateWindow(m_props.m_width, m_props.m_height, m_props.m_title, nullptr, nullptr);  
		}//!< creates window with native parameters

		m_graphicsContext.reset(new GLFW_OpenGLGraphics(m_native)); //!< resets graphics content on window
		m_graphicsContext->init(); //!< init graphics content on window

			glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));//!<  sets user pointer for the window

			glfwSetWindowCloseCallback(m_native,
				[](GLFWwindow * window)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onClose = handler->getOnCloseCallback();
				WindowCloseEvent e;
				onClose(e);
			}
			);//!< sets the window close call back

			glfwSetWindowSizeCallback(m_native,
				[](GLFWwindow * window, int newWidth, int newHeight)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onResize = handler->getOnResizeCallback();
				WindowResizeEvent e(newWidth, newHeight);
				onResize(e);
			}
			);//!< sets the window size call back

			glfwSetWindowFocusCallback(m_native,
				[](GLFWwindow * window, int focused)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));				
				if (focused == GLFW_FOCUSED)
				{
					auto& onFocus = handler->getOnFocusCallback();
					WindowFocusEvent e;
					onFocus(e);
				}
				else 
				{
					auto& onLostFocus = handler->getOnLoseFocusCallback();
					WindowLostFocusEvent e;
					onLostFocus(e);
				}	
			}
			);	//!< sets the window focus call back	
		
			glfwSetWindowPosCallback(m_native,
				[](GLFWwindow* window, int xPos, int yPos)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onWindowMoved = handler->getOnWindowMovedCallback();
				WindowMovedEvent e(xPos, yPos);
				onWindowMoved(e);
			}
			);//!< sets the window position call back


			glfwSetKeyCallback(m_native,
				[](GLFWwindow* window, int keyCode, int scancode, int  action, int mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					auto& onKeyPress = handler->getOnKeyPressCallback();

					KeyPressedEvent e(keyCode, 0) ;
					onKeyPress(e);
				}
				else if (action == GLFW_REPEAT)
				{
					auto& onKeyPress = handler->getOnKeyPressCallback();

					KeyPressedEvent e(keyCode, 1);
					onKeyPress(e);
				}
				else if (action == GLFW_RELEASE)
				{
					auto& onKeyRelease = handler->getOnKeyReleaseCallback();

					KeyReleasedEvent e(keyCode);
					onKeyRelease(e);
				}				
			}				
			);//!< sets the keyboard call back

			glfwSetMouseButtonCallback(m_native,
				[](GLFWwindow* window, int button, int  action, int mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				if (button == GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_PRESS)
				{
					auto& onMouseDown = handler->getOnMouseDownCallback();
					MouseButtonPressedEvent e(button);
					onMouseDown(e);				
				}
				else if (button == GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_RELEASE)
				{
					auto& onMouseUp = handler->getOnMouseUpCallback();
					MouseButtonReleasedEvent e(button);
					onMouseUp(e);
				}
				if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
				{
					auto& onMouseDown = handler->getOnMouseDownCallback();
					MouseButtonPressedEvent e(button);
					onMouseDown(e);
				}
				else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
				{
					auto& onMouseUp = handler->getOnMouseUpCallback();
					MouseButtonReleasedEvent e(button);
					onMouseUp(e);
				}						
			}//!< sets the mouse button call back
			);
			
			glfwSetScrollCallback(m_native,
				[](GLFWwindow* window, double xoffset, double yoffset)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onScroll = handler->getOnMouseScrollCallback();
				MouseScrollEvent e(xoffset, yoffset);
				onScroll(e);	
			}					
			);//!< sets the scroll call back 

			glfwSetCursorPosCallback(m_native,
				[](GLFWwindow* window, double xpos, double ypos)
				{
					EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
					auto& onMouseMoved = handler->getOnMouseMoveCallback();
					MouseMovedEvent e(xpos, ypos);
					onMouseMoved(e);					
				}
			);	//!< sets the cursor position call back 	
	}//!< initilise window properties
	   
	void GLFWWindowImplementation::close() 
	{
		glfwDestroyWindow(m_native);
	}

	void GLFWWindowImplementation::onUpdate(float timestep) 
	{
		glfwPollEvents();
		m_graphicsContext->swapBuffers();
	}

	void GLFWWindowImplementation::setVSync(bool vSync)
	{
		m_props.m_isVSync = vSync;

		if (m_props.m_isVSync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}			
	}



}