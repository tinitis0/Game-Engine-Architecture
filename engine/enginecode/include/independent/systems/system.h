/*! \file system.h*/
#pragma once

#include <cstdarg>

namespace Engine {
	/**
	\enum class SystemSignal, 
	* gets the system signal
	*/
	enum class SystemSignal { None = 0 };

	/**
	\ class System,
	* Interface class for all systems
	*/
	class System
	{
	public:
		virtual ~System() {}; //!< deconstructor
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Stop the system
	};
}
