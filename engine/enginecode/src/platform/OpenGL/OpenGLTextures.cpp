/*! \file OpenGLTextures.h */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLTextures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine
{
	OpenGLTexture::OpenGLTexture(const char * filepath)
	{
		int width, height, channels; //!< set the parameters
		unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0); //!<load image from path to data pointer
		if (data)init(width, height, channels, data);	 //!< init if data	
		stbi_image_free(data); //!< load the image from data
	}//!< OpenGL texture filepath

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{		
		init(width, height, channels, data); //!< init with parameters				
	}//!< OpenGL texture init

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_OpenGL_ID);		
	} //!< deconstructor

	void OpenGLTexture::edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data)
	{		
		if (data)
		{
			if (m_channels == 3) glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //!< if it has 3 channels set the subtexture with parameters
			else if (m_channels == 4) glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); //!< if it has 4 channels set the subtexture with parameters
		}
	} //!< edit the texture with parameters

	void OpenGLTexture::init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		glGenTextures(1, &m_OpenGL_ID); //!< generate texture
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); //!< bind the texture

		// Texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //!< texture parameters clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //!< texture parameters clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //!< texture parameters linear
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //!< texture parameters linear

		if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //!< if it has 3 channels set the image with parameters
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //!< if it has 4 channels set the image with parameters
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);	 //!< generates mipmap for GL 2D texture	

		m_width = width; //!< texture width
		m_height = height; //!< texture height
		m_channels = channels; //!<texture channels
	}
}