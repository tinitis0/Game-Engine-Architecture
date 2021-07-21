/*! \file indexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine 
{
	/** \class IndexBuffer
	* API agnostic index buffer
	*/
	class IndexBuffer 
	{
	public:
		virtual ~IndexBuffer() = default; //!<Deconstructor
		virtual inline uint32_t getRenderID() const = 0; //!< get render ID
		virtual inline uint32_t getCount() const = 0; //!< get render count
		static IndexBuffer* create(uint32_t * indices, uint32_t count); //!< creates the index buffer
	};
}