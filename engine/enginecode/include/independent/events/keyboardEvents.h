/*! \file keyboardEvents.h */
#pragma once

#include "events.h"

namespace Engine {

	/* \class KeyEvent
	* gets the Key code for the Key events
	*/
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int32_t KeyCode) : m_keyCode(KeyCode) {} //!< Get  the key code for the KeyEvent
		int32_t m_keyCode;//!< Assign int to the key code
	public: 
		inline int32_t getKeyCode() const { return m_keyCode;} //!< Get the pressed key 
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; } //!< Get the event category flags
	};

	/* \class KeyPressedEvent
	* Gets the key thats pressed and amount of times its pressed
	*/
	class KeyPressedEvent : public KeyEvent
	{	
	private:
		int32_t m_AmountOfPressed; //!< How many times has pressed event repeated
	public: 
		KeyPressedEvent(int32_t KeyCode, int32_t amountPressed) : KeyEvent(KeyCode), m_AmountOfPressed(amountPressed) {} //<! Constructor
		inline int32_t getAmountPressed() const { return m_AmountOfPressed; }  //!< Return int 
		static EventType getStaticType() { return EventType::KeyPressed; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 
	};

	/* \class KeyReleasedEvent
	* Gets the key thats released 
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	public: 
		KeyReleasedEvent(int32_t KeyCode) : KeyEvent(KeyCode) {} //<! Constructor
		static EventType getStaticType() { return EventType::KeyReleased; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 
	};

	/* \class KeytypedEvent
	* Gets the key that have been used
	*/
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int32_t KeyCode) : KeyEvent(KeyCode) {} //<! Constructor
		static EventType getStaticType() { return EventType::KeyTyped; } //!< Return event type 
		virtual inline EventType getEventType() const override { return getStaticType(); } //!< Return static type 
	};


}