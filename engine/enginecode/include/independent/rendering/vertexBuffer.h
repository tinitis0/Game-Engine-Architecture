/*! \file vertexBuffer.h */
#pragma once

#include <cstdint>
#include <vector>
#include "rendering/bufferLayout.h"

namespace Engine
{
	/** \class VertexBuffer
	* API agnostic vertex buffer
	*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default; //!<Deconstructor
		virtual inline uint32_t getRenderID() const = 0; //!< get render ID
		virtual inline const VertexBufferLayout& getLayout() const = 0; //!< get buffer layout
		static VertexBuffer* create(void* vertices, uint32_t size, const VertexBufferLayout& layout); //!< creates vertex buffer by taking in parameters
	};
}