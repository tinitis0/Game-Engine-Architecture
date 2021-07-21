/*! \file OpenGLIndexBuffer.h */
#pragma once

#include "rendering/indexBuffer.h"

namespace Engine
{
	/** \class OpenGLIndexBuffer
	* Index Buffer for OpenGL
	*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t * indices, uint32_t count); //!< constructor
		virtual ~OpenGLIndexBuffer(); //!<Deconstructor
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< get render ID
		virtual inline uint32_t getCount() const override { return m_count; }	//!< get render count
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_count; //!< Effective draw count
	};
}
