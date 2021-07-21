/*! \file logs.cpp */

#include "engine_pch.h"
#include "systems/logs.h"

namespace Engine 
{
	std::shared_ptr<spdlog::logger> Logs::s_consoleLogger = nullptr; //!< shared pointer for consol logger
	std::shared_ptr<spdlog::logger> Logs::s_fileLogger = nullptr; //!< shared pointer for file logger

	void Logs::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T]: %v%$"); //!< logger pattern
		spdlog::set_level(spdlog::level::trace); //!< logger trace
		s_consoleLogger = spdlog::stdout_color_mt("Consol");//!< consol logger colour
		char filepath[256] = "logs/"; //!< logger filepath
		char time[128]; //!< logger time
		/*
		try
		{
		std::time_t tm = std::time(nullptr);
		std::strftime(time, sizeof(time), "%d_%m_%y %I_%M_%S", std::localtime(&tm));
		strcat_s(filepath, time);
		strcat_s(filepath, ".txt");
		s_fileLogger = spdlog::basic_logger_mt("File", filepath);
		}
		catch (const spdlog::spdlog_ex& e)
		{
			s_consoleLogger->error("Could not start the file logger: {0}", e.what());
			s_fileLogger.reset();
		}
		*/
	} //!< start the logger

	void Logs::stop(SystemSignal close, ...)
	{
		s_consoleLogger->info("Stopping console logger"); //!< log that the legger is stopping
		s_consoleLogger.reset(); //!< reset the logger
	}//!< stop the logger
}