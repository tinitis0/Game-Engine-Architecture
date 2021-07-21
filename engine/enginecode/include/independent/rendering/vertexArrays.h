/*! \file vertexArrays.h */
#pragma once

#include <cstdint>
#include <vector>
#include "rendering/indexBuffer.h"
#include "rendering/vertexBuffer.h"

namespace Engine
{
	/** \class VertexArray
	* API agnostic vertex arrays
	*/
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default; //!<Deconstructor set to default
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; //!< adds vertex buffer, set to 0 by default
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer ) = 0;//!< sets index buffer, set to 0 by default
		inline std::shared_ptr<IndexBuffer> getIndexBuffer() { return m_indexBuffer; }  //!< gets the index buffer
		virtual inline uint32_t getDrawCount() const = 0; //!< Get draw count
		virtual inline uint32_t getRenderID() const = 0; //!< get render ID
		static VertexArray* create(); //!< creates the vertex Arrays

	protected:
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< shared pointer to index buffer
		std::shared_ptr<VertexBuffer> m_vertexBuffers; //!< shared pointer to vertex buffer
	};
}