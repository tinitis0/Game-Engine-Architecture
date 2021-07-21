/*! \file application.h */
#pragma once

#include "systems/logs.h"
#include "core/timer.h"
#include "events/allEvents.h"
#include "core/window.h"
#include "core/inputPoller.h"

namespace Engine {

	/**	\class Application
	* Fundemental class of the engine. A singleton which runs the game loop infinitely.	
	*/
	class Application
	{
	protected:
		Application(); //!< Constructor

		std::shared_ptr<Logs> m_logSystem; //!< log system
		std::shared_ptr<Timer> m_timer; //!< Timer
		std::shared_ptr<System> m_windowSystem; //!< Windows system
		std::shared_ptr<Window> m_window; //!< Window

		bool onClose(WindowCloseEvent& e); //!< Run when the window closes
		bool onResize(WindowResizeEvent& e); //!< Run when the window is resized
		bool onFocus(WindowFocusEvent& e); //!< Run when window is focused on
		bool onLostFocus(WindowLostFocusEvent& e); //!< Run when window has lost focus
		bool onWindowMoved(WindowMovedEvent& e); //!< Run when window has moved

		bool onKeyPressed(KeyPressedEvent& e); //!< Run when Key is pressed
		bool onKeyReleased(KeyReleasedEvent& e);  //!< Run when Key is released
		
		bool onMouseDown(MouseButtonPressedEvent& e); //!< Run when Mouse button is pressed
		bool onMouseUp(MouseButtonReleasedEvent& e); //!< Run when Mouse button is released
		bool onScroll(MouseScrollEvent& e); //!< Run when Mouse scrollwheel is scrolled
		bool onMouseMoved(MouseMovedEvent& e); //!< Run when Mouse is moved	 

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?

	};	
	Application* startApplication(); //!< Function definition which provides an entry hook
}