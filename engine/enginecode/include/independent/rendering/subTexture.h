/*! \file subTexture.h */
#pragma once

#include <platform/OpenGL/OpenGLTextures.h>
#include <memory>
#include <glm/glm.hpp>
namespace Engine
{
	/** \class SubTexture
	* Creates a Sub Textures
	*/
	class SubTexture
	{
	public: 
		SubTexture(); //!< constructor
		SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd ); //!< constructor with parameters
		inline	glm::vec2 getUVStart() { return m_UVStart; } //!< get the UV start point
		inline	glm::vec2 getUVEnd() { return m_UVEnd; } //!< get the UV end point
		glm::ivec2 getSize() { return m_size; } //!< return the size of the subtexture
		glm::vec2 getSizef() { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; } //!< return the size of subtexture as x and y floating point
		inline uint32_t getWidth() { return m_size.x; } //!< get width
		inline uint32_t getHeight() { return m_size.y; } //!< get height
		inline uint32_t getWidthf() { return static_cast<float>(m_size.x); } //!< get width floating point
		inline uint32_t getHeightf() { return static_cast<float>(m_size.y); } //!< get height floating point
		float transformU(float U); //!< Transform original to atlaseed co-ordinates
		float transformV(float V);//!< Transform original to atlaseed co-ordinates
		glm::vec2 transformUV(glm::vec2 UV);//!< Transform original to atlaseed co-ordinates
	private:
		std::shared_ptr <Texture> m_texture; //!< holds texture
		glm::vec2 m_UVStart; //!< holds UV Start point
		glm::vec2 m_UVEnd;  //!< holds UV End point
		glm::ivec2 m_size; //!< size in pixels
	};
}
 