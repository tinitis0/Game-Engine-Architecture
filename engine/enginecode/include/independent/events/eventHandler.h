/*! \file eventHandler.h */
#pragma once

#include "allEvents.h"
#include <functional>

namespace Engine
{
	/* \class EventHandler
	* handles the input events
	*/
	class EventHandler
	{
	private:
		std::function<bool(WindowCloseEvent&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(WindowFocusEvent&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(WindowLostFocusEvent&)> m_onLossFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(WindowMovedEvent&)> m_onWindowMovedCallback = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(KeyPressedEvent&)> m_onKeyPressedCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleasedCallback = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(MouseButtonPressedEvent&)> m_onMouseDownCallback = std::bind(&EventHandler::defaultOnMouseDown, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(MouseButtonReleasedEvent&)> m_onMouseUpCallback = std::bind(&EventHandler::defaultOnMouseUp, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(MouseScrollEvent&)> m_onMosueScrollCallback = std::bind(&EventHandler::defaultOnMouseScroll, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1); //!< holds function which is veriable, bounds this function to bool function


		bool defaultOnClose(WindowCloseEvent& e) { return false; } //!< function. default behaviour when window Close event happens. returns false. not handled.
		bool defaultOnResize(WindowResizeEvent& e) { return false; } //!< function. default behaviour when window Resize event happens. returns false. not handled.
		bool defaultOnFocus(WindowFocusEvent& e) { return false; } //!< function. default behaviour when window Focus event happens. returns false. not handled.
		bool defaultOnLostFocus(WindowLostFocusEvent& e) { return false; } //!< function. default behaviour when window Lose Focus event happens. returns false. not handled.
		bool defaultOnWindowMoved(WindowMovedEvent& e) { return false; } //!< function. default behaviour when window Moved event happens. returns false. not handled.
		bool defaultOnKeyPress(KeyPressedEvent& e) { return false; } //!< function. default behaviour when key Pressed event happens. returns false. not handled.
		bool defaultOnKeyRelease(KeyReleasedEvent& e) { return false; } //!< function. default behaviour when key Released event happens. returns false. not handled.
		bool defaultOnKeyTyped(KeyTypedEvent& e) { return false; } //!< function. default behaviour when key Typed event happens. returns false. not handled.
		bool defaultOnMouseDown(MouseButtonPressedEvent& e) { return false; } //!< function. default behaviour when mouse Button Pressed event happens. returns false. not handled.
		bool defaultOnMouseUp(MouseButtonReleasedEvent& e) { return false; } //!< function. default behaviour when mouse Button Release event happens. returns false. not handled.
		bool defaultOnMouseScroll(MouseScrollEvent& e) { return false; } //!< function. default behaviour when mouse Scroll event happens. returns false. not handled.
		bool defaultOnMouseMoved(MouseMovedEvent& e) { return false; } //!< function. default behaviour when mouse Moved event happens. returns false. not handled.


	public:
		void setOnCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }  //!< sets the window close call back event
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; } //!< sets the window resize call back event
		void setOnFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusCallback = fn; } //!< sets the window focus call back event
		void setOnLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLossFocusCallback = fn; } //!< sets the window lose focus call back event
		void setOnWindowMovedCallback(const std::function<bool(WindowMovedEvent&)>& fn) { m_onWindowMovedCallback = fn; }//!< sets the window moved call back event
		void setOnKeyPressCallback(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressedCallback = fn; } //!< sets the key pressed call back event
		void setOnKeyReleaseCallback(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleasedCallback = fn; } //!< sets the key released call back event
		void setOnKeyTypedCallback(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedCallback = fn; } //!< sets the key typed call back event
		void setOnMouseDownCallback(const std::function<bool(MouseButtonPressedEvent&)>& fn) { m_onMouseDownCallback = fn; } //!< sets the mouse button down call back event
		void setOnMouseUpCallback(const std::function<bool(MouseButtonReleasedEvent&)>& fn) { m_onMouseUpCallback = fn; } //!< sets the mouse button up cakk back event
		void setOnMouseScrollCallback(const std::function<bool(MouseScrollEvent&)>& fn) { m_onMosueScrollCallback = fn; } //!< sets the mouse scroll  call back event
		void setOnMouseMovedCallback(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedCallback = fn; } //!<sets the mouse moved call back event

		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback()  {return m_onCloseCallback; } //!< passes reference to window close call back
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeCallback; } //!< passes reference to window resize call back
		std::function<bool(WindowFocusEvent&)>& getOnFocusCallback() { return m_onFocusCallback; } //!< passes reference to  window focus on call back
		std::function<bool(WindowLostFocusEvent&)>& getOnLoseFocusCallback() { return m_onLossFocusCallback; } //!< passes reference to window lose focus call back 
		std::function<bool(WindowMovedEvent&)>& getOnWindowMovedCallback() { return m_onWindowMovedCallback; } //!< passes reference to window moved call back
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressCallback() { return m_onKeyPressedCallback; } //!< passes reference to key pressed call back
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleaseCallback() { return m_onKeyReleasedCallback; } //!< passes reference to key relseased call back  
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedeCallback() { return m_onKeyTypedCallback; } //!< passes reference to key typed call back
		std::function<bool(MouseButtonPressedEvent&)>& getOnMouseDownCallback() { return m_onMouseDownCallback; } //!< passes reference to mouse down call back
		std::function<bool(MouseButtonReleasedEvent&)>& getOnMouseUpCallback() { return m_onMouseUpCallback; } //!< passes reference to mouse up call back
		std::function<bool(MouseScrollEvent&)>& getOnMouseScrollCallback() { return m_onMosueScrollCallback; } //!< passes reference to mouse scroll call back
		std::function<bool(MouseMovedEvent&)>& getOnMouseMoveCallback() { return m_onMouseMovedCallback; } //!< passes reference to mouse moved call back

	};
}
