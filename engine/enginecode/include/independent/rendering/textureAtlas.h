/*! \file textureAtlas.h */
#pragma once

#include <vector>
#include "rendering/subTexture.h"

namespace Engine
{	
	struct  SimpleRect { uint32_t x, y, w, h; };

	/** \class TextureAtlas
	* 
	*/
	class TextureAtlas
	{
	public:
		TextureAtlas(glm::ivec2 size = { 4069, 4069 }, uint32_t channels = 4, uint32_t reservedSpaces = 32); //!< constructor which takes size and channels and with preallocated 32 spaces
		bool add(const char * filepath, SubTexture& result); //!< Attempt to add a subtrexture with a file
		bool add(uint32_t Width, uint32_t height, uint32_t channels, unsigned char * data, SubTexture& result); //!< Attempt to add a subtrexture wwhich takes in data
		inline uint32_t getChannels() const{return m_baseTexture->getChannels();} //!< gets the texture channels
		inline std::shared_ptr<Texture> getBaseTexture() const { return m_baseTexture;}//!< gets the base texture 
		inline uint32_t getID() const { return m_baseTexture->getID();}//!< gets the texture ID
	private:
		std::vector<SimpleRect> m_spaces; //!< Gaps left which can be filled
		std::shared_ptr<Texture> m_baseTexture; //!< texture which holds all subtexture pixel data
	};
}