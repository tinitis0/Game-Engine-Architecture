/*! \file logs.h */
#pragma once

#include "system.h"
#include <spdlog/spdlog.h>

namespace Engine
{
	/* \class Logs
	* file and console loggers
	*/
	class Logs : public System
	{
	public:
		
		virtual void start(SystemSignal init = SystemSignal::None, ...) override; //!<Start the logger
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Stop the logger

		template<class ...Args>
		static void info(Args&&... args);

		template<class ...Args>
		static void trace(Args&&... args);

		template<class ...Args>
		static void warn(Args&&... args);

		template<class ...Args>
		static void debug(Args&&... args);

		template<class ...Args>
		static void error(Args&&... args);

		template<class ...Args>
		static void release(Args&&... args);

		template<class ...Args>
		static void file(Args&&... args);

	private:
		static std::shared_ptr < spdlog::logger> s_consoleLogger; // !<Console logger
		static std::shared_ptr < spdlog::logger> s_fileLogger; // !<File logger
	}; 

	template<class ...Args>
	static void Logs::debug(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->debug(std::forward<Args>(args) ...); //!< console logger debug
#endif // NG_DEBUG		
	}
	template<class ...Args>
	static void Logs::error(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->error(std::forward<Args>(args) ...); //!< console logger error
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Logs::info(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->info(std::forward<Args>(args) ...); //!< console logger info
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Logs::trace(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->trace(std::forward<Args>(args) ...);//!< console logger trace 
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Logs::warn(Args&&... args)
	{
#ifdef NG_DEBUG
		s_consoleLogger->warn(std::forward<Args>(args) ...); //!< console logger warning
#endif // NG_DEBUG
	}

	template<class ...Args>
	static void Logs::release(Args&&... args)
	{
		s_consoleLogger->trace(std::forward<Args>(args) ...); //!< console logger release
	}

	template<class ...Args>
	static void Logs::file(Args&&... args)
	{
		if (s_fileLogger) s_fileLogger->trace(std::forward<Args>(args) ...); //!< file logger trace
	}
}