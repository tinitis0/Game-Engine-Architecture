/*! \file OpenGLUniformBuffer.h */
#pragma once

#include "rendering/uniformBuffer.h"

namespace Engine
{
	/**	\class OpenGLUniformBuffer
	* Uniform buffers for OpenGL code
	*/
	class OpenGLUniformBuffer : public UniformBuffer
	{
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID		
		static uint32_t s_blockNumber; //!< Global block number
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< constructor
		~OpenGLUniformBuffer() override; //!<Deconstructor
		inline uint32_t getRenderID() override{ return m_OpenGL_ID; } //!< gets the render ID
		inline UniformBufferLayout getLayout() override{ return m_layout; } //!< gets the uniform buffer layout 
		void attachShaderBlock(const std::shared_ptr<Shaders>& shader, const char * blockName) override; //!< attaches shader block to uniform buffer
		void uploadData(const char * uniformName, void * data) override; //!< uploads data to uniform buffer
	};
}