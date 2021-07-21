/*! \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Engine::Application* Engine::startApplication(); //!< starting point for the application

int main(int argc, char** argv)
{
	auto application = Engine::startApplication(); //!< automatically sets the application to startApplication
	application->run(); //!< runs the application
	delete application; //!< deletes the application

	return 0; 
}

