/*! \file OpenGLVertexBuffer.h */
#pragma once

#include "rendering/bufferLayout.h"
#include "rendering/vertexBuffer.h"

namespace Engine
{
	/** \class OpenGLVertexBuffer
	* Vertex Buffer for OpenGL
	*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); //!<Constructor with parameters
		virtual ~OpenGLVertexBuffer(); //!<Deconstructor
		void edit(void* vertices, uint32_t size, uint32_t offset);//!< edit data
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< get render ID
		virtual inline const VertexBufferLayout& getLayout() const override { return m_layout; } //!< get render layout
	private:
		uint32_t m_OpenGL_ID; //!< Render ID 
		VertexBufferLayout m_layout;//!< Buffer layout			   
	};
}

