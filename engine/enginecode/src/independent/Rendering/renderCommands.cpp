/*! \file renderCommands.cpp */

#include "engine_pch.h"
#include "rendering/renderCommands.h"
#include "rendering/renderAPI.h"
#include <glad/glad.h>

namespace Engine
{
	std::function<void(void)> Engine::RenderCommandFactory::getClearColourAndDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
			case RenderAPI::API::Direct3D:
				return std::function<void(void)>();
			case RenderAPI::API::None:
				return std::function<void(void)>();
			case RenderAPI::API::OpenGL:
				return []() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); };//!< clears OpenGL Depth and Colour Buffer
			case RenderAPI::API::Vulkan:
				return std::function<void(void)>();
			default:
				return std::function<void(void)>();
		}		
	}

	std::function<void(void)> RenderCommandFactory::getSetClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return [r, g, b, a]() { glClearColor(r, g, b, a); };//!< creates clear colour from OpenGL 
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}

		return std::function<void(void)>();
	}
	std::function<void(void)> RenderCommandFactory::getClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() { glClear(GL_COLOR_BUFFER_BIT ); };//!< clears OpenGL Colour Buffer
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}	
		return std::function<void(void)>();
	}

	std::function<void(void)> RenderCommandFactory::getClearDepthCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() { glClear(GL_DEPTH_BUFFER_BIT); }; //!< clears OpenGL Depth Buffer
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
}


