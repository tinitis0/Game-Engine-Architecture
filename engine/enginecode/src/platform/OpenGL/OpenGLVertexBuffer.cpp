/*! \file OpenGLVertexBuffer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLVertexBuffer.h"
 
namespace Engine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(void * vertices, uint32_t size, VertexBufferLayout layout) : m_layout(layout)
	{
		glCreateBuffers(1, &m_OpenGL_ID); //!< create the buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID); //!< bind the buffer
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW); //!< get buffer data
	} //!< constructor with parameters

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);  //!< delete buffers
	} //!< deconstructor

	void OpenGLVertexBuffer::edit(void * vertices, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_OpenGL_ID); //!< bind the buffer
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices); //!< get buffer sub data
	} //!< edit OpenGL vertex buffer
}