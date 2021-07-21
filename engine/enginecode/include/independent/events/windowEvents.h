/*! \file windowsEvents.h */
#pragma once

#include "events.h"
#include<glm/glm.hpp>

namespace Engine
{
	/* \class WindowCloseEvent
	* Closes the window
	*/
	class WindowCloseEvent : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!< Return static type 
		virtual EventType getEventType()const override { return EventType::WindowClose; }; //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }; //!< Get the event category flags
	};

	/* \class WindowResizeEvent
	* Resizes the window and gets the parameters
	*/
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) :  //<! Constructor
			m_width(width), 
			m_height(height) 
		{}
		static EventType getStaticType() { return EventType::WindowResize; } //!< Return static type 
		virtual EventType getEventType()const override { return EventType::WindowResize; }; //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }; //!< Get the event category flags

		inline int32_t getWidth() const { return m_width; } //!< Get width
		inline int32_t getHeight() const { return m_height; } //!< Get height
		inline glm::ivec2 getSize() const
		{
			return{ m_width, m_height };
		} //!< Return position
		
	private:
		int32_t m_width;	//!< Window width after resize
		int32_t m_height;	//!< Window height after resize
	};
	   
	/* \class WindowMoveEvent
	* Moves the window and gets the position of it
	*/
	class WindowMovedEvent : public Event
	{
	private:
		int32_t	m_xPosition; //!< Windows position on X axis after its moved
		int32_t m_yPosition; //!< Windows position on Y axis after its moved
	public:
		WindowMovedEvent(int32_t X, int32_t Y) : m_xPosition(X), m_yPosition(Y) {}
		static EventType getStaticType() { return EventType::WindowMoved; } //!< Return static type 
		virtual inline EventType getEventType() const override { return EventType::WindowMoved; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; }; //!< Get the event category flags
		inline int32_t getXPosition() const { return m_xPosition; } //!< Get X Position
		inline int32_t getYPosition() const { return m_yPosition; } //!< Get Y Position
		inline glm::ivec2 getPos() const  
		{
			return{ m_xPosition, m_yPosition };
		} //!< Return position
	};

	/* \class WindowFocusEvent
	* Focuses once the window is open 
	*/
	class WindowFocusEvent : public Event
	{
	public: 
		WindowFocusEvent() {} //<! Constructor
		static EventType getStaticType() { return EventType::WindowFocus; } //!< Return static type 
		virtual inline EventType getEventType() const override { return EventType::WindowFocus; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; }; //!< Get the event category flags
	};

	/* \class WindowLostFocusEvent
	* Unfocuses once the window is in background
	*/
	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {} //<! Constructor
		static EventType getStaticType() { return EventType::WindowLostFocus; } //!< Return static type 
		virtual inline EventType getEventType() const override { return EventType::WindowLostFocus; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; }; //!< Get the event category flags
	};	
}