/*! \file timer.h */
#pragma once

#include <chrono>

namespace Engine
{
	/** \class Timeer  
	* Interface class for timer	
	*/
	class Timer
	{
	public:
		virtual void start() = 0; //!< Start the timer
		virtual void reset() = 0;//!< Reset the timer	
		virtual float getElapsedTime() = 0; //!< get the elapsed time since last start or reset
	};
	

	/** \class Time 
	* chrono timer class
	*/
	class ChronoTimer : public Timer
	{
	public:
		virtual inline void start() override { m_startPoint = std::chrono::high_resolution_clock::now(); } //!< starts the chrono timer
		virtual inline void reset() override { m_startPoint = std::chrono::high_resolution_clock::now(); } //!< resets the chrono timer
		virtual float getElapsedTime() override //!< gets the elapsed time
		{
			m_endPoint = std::chrono::high_resolution_clock::now(); //!< sets the endpoint for the timer
			std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint; //!< sets the clock to be in miliseconds
			return  elapsed.count() / 1000.f; //!< returns elapsed time divided by 1000
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;//!< Start time for the timer
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint; //!< End time for the timer

	};

}
