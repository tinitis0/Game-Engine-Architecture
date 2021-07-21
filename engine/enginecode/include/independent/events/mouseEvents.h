/*! \file mouseEvents.h */
#pragma once

#include "events.h"
#include <glm/glm.hpp>

namespace Engine {

	/* \class MouseEvent
	* gets the mouse input
	*/
	class MouseEvent : public Event
	{
	public:
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; } //!< Get the event category flags
	};

	/* \class MouseMovedvent
	* gets the mouse position
	*/
	class MouseMovedEvent : public MouseEvent
	{
	private:
		float m_mouseXPos, m_mouseYPos; //!< set float for Mouse X and Y position

	public:
		MouseMovedEvent(float X, float Y) : m_mouseXPos(X), m_mouseYPos(Y) {} //<! Constructor
		static EventType getStaticType() { return EventType::MouseMoved; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 

		inline float getXPos() const { return m_mouseXPos; } //!< Get Mouse X position
		inline float getYPos() const { return m_mouseYPos; } //!< Get Mouse Y position
		inline glm::vec2 getPos() const { return glm::vec2(m_mouseXPos, m_mouseYPos); }  //!< 2D vector for mouse position  
	};

	/* \class MouseButtonPressedEvent
	* gets the mouse button pressed ID
	*/
	class MouseButtonPressedEvent : public MouseEvent
	{
	private:
		int32_t m_pressedButton; //!< Set the pressed button as int32_t 
	public:

		MouseButtonPressedEvent(int32_t pressedButton) : m_pressedButton(pressedButton) {} //<! Constructor
		
		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 
		inline int32_t getPressedButton() const { return m_pressedButton; } //!< Get the pressed button

	};

	/* \class MouseButtonReleasedEvent
	* gets the mouse button released ID
	*/
	class MouseButtonReleasedEvent : public MouseEvent
	{
	private:
		int32_t m_releasedButton; //!< Set the released button as int32_t 
	public:

		MouseButtonReleasedEvent(int32_t releasedButton) : m_releasedButton(releasedButton) {} //<! Constructor

		static EventType getStaticType() { return EventType::MouseButtonReleased; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 
		inline int32_t getreleasedButton() const { return m_releasedButton; } //!< Get the pressed button

	};

	/* \class MouseScrollEvent
	* gets the mouse scroll wheel input
	*/
	class MouseScrollEvent : public MouseEvent
	{
	private:
		float m_mouseXOffset, m_mouseYOffset; //!< set float for Mouse offset X and Y position

	public:
		MouseScrollEvent(float XOffsetPos, float YOffsetPos) : m_mouseXOffset(XOffsetPos), m_mouseYOffset(YOffsetPos) {} //<! Constructor
		static EventType getStaticType() { return EventType::MouseScrolled; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 

		inline float getXOffsetPos() const { return m_mouseXOffset; } //!< Get Mouse X offset position
		inline float getYOffsetPos() const { return m_mouseYOffset; } //!< Get Mouse Y offset position

	};

}