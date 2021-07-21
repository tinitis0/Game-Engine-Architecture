#pragma once

#include <gtest/gtest.h>

#include "events/eventHandler.h"


class MockApplication
{
private:		
	//	MouseScrolled

	//Window Events
	bool onClose(Engine::WindowCloseEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool WindowResize(Engine::WindowResizeEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool WindowFocus(Engine::WindowFocusEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool WindowLostFocus(Engine::WindowLostFocusEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool WindowMoved(Engine::WindowMovedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	//Keyboard Events
	bool KeyPressed(Engine::KeyPressedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool KeyReleased(Engine::KeyReleasedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool KeyTyped(Engine::KeyTypedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	//Mouse Events
	bool MouseButtonPressed(Engine::MouseButtonPressedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool MouseButtonReleased(Engine::MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool MouseMoved(Engine::MouseMovedEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}
	bool MouseScroll(Engine::MouseScrollEvent& e)
	{
		e.handle(true);
		return e.ishandled();
	}

public:
	Engine::EventHandler m_handler;
	//Window Events
	void setCloseCallback()
	{
		m_handler.setOnCloseCallback(std::bind(&MockApplication::onClose, this, std::placeholders::_1));
	}
	void setResizeCallback()
	{
		m_handler.setOnResizeCallback(std::bind(&MockApplication::WindowResize, this, std::placeholders::_1));
	}
	void setFocusCallback()
	{
		m_handler.setOnFocusCallback(std::bind(&MockApplication::WindowFocus, this, std::placeholders::_1));
	}
	void setLostFocusCallback()
	{
		m_handler.setOnLostFocusCallback(std::bind(&MockApplication::WindowLostFocus, this, std::placeholders::_1));
	}
	void setWindowMovedCallback()
	{
		m_handler.setOnWindowMovedCallback(std::bind(&MockApplication::WindowMoved, this, std::placeholders::_1));
	}
	//Keyboard Events
	void setKeyPressedCallback()
	{
		m_handler.setOnKeyPressCallback(std::bind(&MockApplication::KeyPressed, this, std::placeholders::_1));
	}
	void setKeyReleasedCallback()
	{
		m_handler.setOnKeyReleaseCallback(std::bind(&MockApplication::KeyReleased, this, std::placeholders::_1));
	}
	void setKeyTypedCallback()
	{
		m_handler.setOnKeyTypedCallback(std::bind(&MockApplication::KeyTyped, this, std::placeholders::_1));
	}
	//Mouse Events
	void setMouseButtonPressedCallback()
	{
		m_handler.setOnMouseDownCallback(std::bind(&MockApplication::MouseButtonPressed, this, std::placeholders::_1));
	}
	void setMouseButtonReleasedCallback()
	{
		m_handler.setOnMouseUpCallback(std::bind(&MockApplication::MouseButtonReleased, this, std::placeholders::_1));
	}
	void setMouseMovedCallback()
	{
		m_handler.setOnMouseMovedCallback(std::bind(&MockApplication::MouseMoved, this, std::placeholders::_1));
	}
	void setMouseScrollCallback()
	{
		m_handler.setOnMouseScrollCallback(std::bind(&MockApplication::MouseScroll, this, std::placeholders::_1));
	}


};