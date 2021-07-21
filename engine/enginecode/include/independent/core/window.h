/*! \file window.h */
#pragma once

#include "events/eventHandler.h"
#include "core/graphicsContext.h" 

namespace Engine
{
	/** \Class Window Properties
	* Properties for the window to take in
	*/	

	struct WindowProperties //!< Windows Properties
	{
		char * m_title; //!< window title
		uint32_t m_width; //!< window width
		uint32_t m_height; //!< window height
		bool m_isFullScreen; //!<  bool if window full screen
		bool m_isVSync; //!< bool is vSynce on

		WindowProperties(char* title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullScreen = false) : m_title(title), m_width(width), m_height(height), m_isFullScreen(fullScreen) {} //!< window constructor, takes in window properties
	};

	/** \Class Window
	* Abstract windows base class. All Implemented windows go to this interface.
	*/
	class Window 
	{
	protected:
		EventHandler m_handler; //!< Event Handler
		std::shared_ptr<GraphicsContext> m_graphicsContext; //!< Pointer to Graphics context

	public:
		virtual void init(const WindowProperties& properties) = 0; //!< initilising routine 
		virtual void close() = 0; //!< close
		virtual ~Window() {}; //!<virtual constructor
		virtual void onUpdate(float timestep) = 0; //!< on update function
		virtual void setVSync(bool vSync) = 0; //!< gets the refresh rate
		virtual unsigned int getWidth() const = 0; //!< width of window
		virtual unsigned int getHeight() const = 0;//!< height of window
		virtual void* getNativeWindow() const = 0; //!< gets the underlying platform
		virtual bool isFullScreenMode() const = 0; //!< fullscreen mode
		virtual bool isVSync() const = 0; //!< vSync

		inline EventHandler& getEventHandler() { return m_handler; }//!< gets event handler
		
		static Window* create(const WindowProperties& properties = WindowProperties()); //!< Create window with properties

	};





}