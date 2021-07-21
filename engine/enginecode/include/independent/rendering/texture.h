/*! \file texture.h */
#pragma once

#include <cstdint>

namespace Engine
{
	/*! \class Textures
	* \brief API agnostic textures 
	*/
	class Texture
	{
	public:
		virtual ~Texture() = default; //!<Deconstructor
		virtual inline uint32_t getID() const = 0; //!< get render ID
		virtual inline uint32_t getWidth() const = 0;//!< get width
		virtual inline uint32_t getHeight() const = 0;//!< get height
		virtual inline uint32_t getWidthf() const = 0;//!< get width floating point
		virtual inline uint32_t getHeightf() const = 0; //!< get height floating point
		virtual inline uint32_t getChannels() const = 0;//!<  get colour channels
		static Texture* create(const char * filepath); //!< creates the texture takes in filepath
		static Texture* create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< creates the textures takes in parameters
		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) = 0;//!< allows to edit the texture
	};
}