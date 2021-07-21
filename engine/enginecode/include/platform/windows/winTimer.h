/*! \file winTimer.h */
#pragma once

#include <Windows.h>
#include "core/timer.h"

namespace Engine
{
	/** \file WinTimer.h
	* Windows specific timer which use queryPerformanceCount
	*/
	class WinTimer : public Timer
	{
	public:
		virtual void start() override
		{
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_startTime);
		}; //!< starts the timer

		virtual inline void reset() override { QueryPerformanceCounter(&m_startTime); }; //!< resets the timer

		virtual float getElapsedTime() override
		{
		QueryPerformanceCounter(&m_endTime); 
			float result = (m_endTime.QuadPart - m_startTime.QuadPart) * 1000.0 / m_frequency.QuadPart; //!< calculates the result
			result /= 1000.f; //!< divides the result by 1000
			return result; //!< returns the result after dividing it
		} //!< gets the elasped time
	private:
		LARGE_INTEGER m_startTime; //!< Start time for the timer
		LARGE_INTEGER m_endTime; //!< End time for the timer
		LARGE_INTEGER m_frequency; //!< Ticks per second of CPU
	};
}
