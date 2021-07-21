/*! \file OpenGLIndexBuffer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include  "platform/OpenGL/OpenGLIndexBuffer.h"

namespace Engine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count) : m_count(count)
	{
		glCreateBuffers(1, &m_OpenGL_ID); //!< creates index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID); //!< binds the index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW); //!< gets the index buffer data
	}//!< OpenGL index buffers

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID); //!< deletes the index buffer
	} //!< deconstructor
}