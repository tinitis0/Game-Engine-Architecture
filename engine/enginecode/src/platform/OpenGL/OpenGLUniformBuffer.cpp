/*! \file OpenGLUniformBuffer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLUniformBuffer.h"

namespace Engine
{
	uint32_t OpenGLUniformBuffer::s_blockNumber = 0; //!< block number from uniform buffer

	OpenGLUniformBuffer::OpenGLUniformBuffer(const UniformBufferLayout & layout) 
	{
		m_blockNumber = s_blockNumber; //!< sets the block number
		s_blockNumber++; //!< adds 1 block number
		m_layout = layout; //!< sets the layout
		glGenBuffers(1, &m_OpenGL_ID); //!< generates the buffer
		glBindBuffer(GL_UNIFORM_BUFFER, m_OpenGL_ID); //!< binds the uniform buffer
		glBufferData(GL_UNIFORM_BUFFER, m_layout.getStride(), nullptr, GL_DYNAMIC_DRAW); //!< gets uniform buffer data
		glBindBufferRange(GL_UNIFORM_BUFFER, m_blockNumber, m_OpenGL_ID, 0, m_layout.getStride()); //!< bind the uniform bugger range

		for (auto& element : m_layout)
		{
			m_uniformCache[element.m_name] = std::pair<uint32_t, uint32_t>(element.m_offset, element.m_size); //!< catch element offset and size to name
		}
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID); //!< delete the buffer
	} //!< deconstructor

	void OpenGLUniformBuffer::attachShaderBlock(const std::shared_ptr<Shaders>& shader, const char * blockName)
	{
		uint32_t blockIndex = glGetUniformBlockIndex(shader->getID(), blockName); //!< get block index
		glUniformBlockBinding(shader->getID(), blockIndex, m_blockNumber); //!< bind the uniform block
	} //!< attach OpenGL uniform buffer to shader block 

	void OpenGLUniformBuffer::uploadData(const char * uniformName, void * data)
	{
		auto& pair = m_uniformCache[uniformName]; //!< pai uniform buffer catch
		glBufferSubData(GL_UNIFORM_BUFFER, pair.first, pair.second, data);	//!< get sub data for the buffer	
	} //!< upl;oad data to OpenGL uniform buffer



}

