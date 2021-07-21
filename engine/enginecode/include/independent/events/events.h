/*! \file events.h */
#pragma once
#include <intTypes.h>
namespace Engine
{
	/* \enum EventType
	* All event types
	*/

	enum class EventType
	{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, 
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	}; //!< Events for window, keyboard and mouse

	/* \enum EventsCategory
	* all event type, category flags
	*/

	enum EventCategory
	{
		none = 0,
		EventCategoryWindow = 1 << 0,   //!< 00000001
		EventCategoryInput = 1 << 1,   //!< 00000010
		EventCategoryKeyboard = 1 << 2,   //!< 00000100
		EventCategoryMouse = 1 << 3,   //!< 00001000
		EventCategoryMouseButton = 1 << 4   //!< 00010000
	};

	/* \enum Events
	* Event base class
	*/

	class Event
	{
	public:
		virtual EventType getEventType() const = 0; //!< Get the event type
		virtual int32_t getCategoryFlags() const = 0; //!< Get the event category flags
		inline bool ishandled() const { return m_ishandled; }//!< Has the event been handled
		inline void handle(bool isHandled) { m_ishandled = isHandled; } //!<Handle the event
		inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; } //!< Is the event in category
	protected:
		bool m_ishandled = false; //!< Has the evenet type been handled
	};




}