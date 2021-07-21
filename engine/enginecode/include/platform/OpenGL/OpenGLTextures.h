/*! \file OpenGLTextures.h */
#pragma once

#include <cstdint>
#include "rendering/texture.h"

namespace Engine
{
	/** \class OpenGLTexture
	* Creates a Textures in OpenGL
	*/
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const char * filepath); //!< Constructor only takes single file
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Constructor which takes multiple parameters 
		virtual ~OpenGLTexture(); //!<Deconstructor
		void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data);  //!<  edit the texture
		virtual inline uint32_t getID() const override { return m_OpenGL_ID; }  //!< get OpenGL ID
		virtual inline uint32_t getWidth() const override  { return m_width; } //!< get width
		virtual inline uint32_t getHeight() const override  { return m_height; } //!< get height
		virtual inline uint32_t getWidthf() const override  { return static_cast<float>(m_width); } //!< get width floating point
		virtual inline uint32_t getHeightf() const override  { return static_cast<float>(m_height);} //!< get height floating point
		virtual inline uint32_t getChannels() const override  { return m_channels;} //!<  get colour channels
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID 
		uint32_t m_width; //!<  Width
		uint32_t m_height; //!<  Height
		uint32_t m_channels; //!< Colour channels
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< initilise texture
	};
}