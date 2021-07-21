/*! \file OpenGLVertexArray.h */
#pragma once

#include <vector>
#include "rendering/vertexArrays.h"

namespace Engine
{
	/** \class OpenGLVertexArray
	* Vertex Array for OpenGL
	*/
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(); //!< Default constructor
		virtual ~OpenGLVertexArray(); //!< Deconstructor
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer); //!< adds vertex buffer to vertex array with shared pointer
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer); //!< adds index buffer to vertex array with shared pointer
		virtual inline uint32_t getDrawCount() const override {if (m_indexBuffer) {return m_indexBuffer->getCount(); }	else { return 0; } }//!< Get draw count
		virtual inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< get render ID
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0;//!< Vertex array attribute index
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer; //!< Shared pointer to vertex buffer
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< Shared pointer to index buffer
	};
}