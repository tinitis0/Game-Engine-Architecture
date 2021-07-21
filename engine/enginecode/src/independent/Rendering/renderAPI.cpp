/*! \file renderAPI.cpp */

#include "engine_pch.h"
#include "rendering/renderAPI.h"
#include "systems/logs.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLTextures.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"


namespace Engine
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL; //!<  sets the API to be OpenGL by default
	   
	IndexBuffer* IndexBuffer::create(uint32_t * indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None :
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		} //!< swich cases to choose which engine code to use                
		return nullptr;
	}//!< creates index buffer 

	VertexBuffer * VertexBuffer::create(void* vertices, uint32_t size, const VertexBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;
	}//!< creates vertex buffer 

	Texture * Texture::create(const char * filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;
	}//!< creates Textures with filepath

	Texture * Texture::create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(width, height, channels, data);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;
	}//!< creates textures with parameters

	Shaders * Shaders::create(const char* vertexFilepath, const char* fragmentFilepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexFilepath, fragmentFilepath);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;
	}//!< creates shaders with vertex and fragment filepaths

	Shaders * Shaders::create(const char* filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;	
	}//!< creates shader with filepath

	VertexArray * VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;
	}//!< creates vertex arrary

	UniformBuffer * UniformBuffer::create(const UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Logs::error("Not having a rendering API is not currently supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer( layout);
			break;
		case RenderAPI::API::Direct3D:
			Logs::error("Direct3D is not currently supported");
			break;
		case RenderAPI::API::Vulkan:
			Logs::error("Vulkan is not currently supported");
			break;
		}//!< swich cases to choose which engine code to use  
		return nullptr;
	}//!< creates uniform buffer by taking UB layout
}



