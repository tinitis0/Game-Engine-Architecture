/*! \file UniformBuffer.h */
#pragma once

#include<ctype.h>
#include <memory>
#include <unordered_map>
#include "rendering/bufferLayout.h"
#include "rendering/shaders.h"

namespace Engine
{
	/** \class UniformBuffer
	* API agnostic uniform buffer
	*/
	class 
		UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default; //!<Deconstructor
		virtual  uint32_t getRenderID() = 0; //!< gets the render ID, which is set to 0
		virtual UniformBufferLayout getLayout() = 0; //!< gets the uniform buffer layout which is set to 0
		virtual void attachShaderBlock(const std::shared_ptr<Shaders>& shader, const char * blockName) = 0; //!< attaches shader block to uniform buffer
		virtual void uploadData(const char * uniformName, void * data) = 0; //!< uploads data to uniform buffer
		static UniformBuffer* create( const UniformBufferLayout& layout); //!< creates the uniform buffer by taking in the layout

	protected:
		UniformBufferLayout m_layout; //!< Uniform buffer layout
		std::unordered_map<const char *, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
		uint32_t m_blockNumber; //!< Block number for this UBO
	};


}