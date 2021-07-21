/*! \file subTexture.h */

#include "engine_pch.h"
#include "rendering/subTexture.h"

namespace Engine
{
	SubTexture::SubTexture()
	{
	} //!< default constructor for subtextures

	SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2 & UVStart, const glm::vec2 & UVEnd) : 
		m_texture(texture), //!< texture
		m_UVStart(UVStart), //!< UV start
		m_UVEnd(UVEnd) //!< UV end
	{
		m_size.x = static_cast<int>(m_UVEnd.x - m_UVStart.x) * m_texture->getWidthf(); //!< gets the size in X
		m_size.y = static_cast<int>(m_UVEnd.y - m_UVStart.y) * m_texture->getHeightf(); //!< gets the size in Y
	}//!< constructor that takes in parameters

	float SubTexture::transformU(float U)
	{
		return m_UVStart.x + ((m_UVEnd.x - m_UVStart.x) * U); //!< returns U from UV
	}//!< subtextures transform U

	float SubTexture::transformV(float V)
	{
		return m_UVStart.y + ((m_UVEnd.y - m_UVStart.y) * V); //!< returns V from UV
	} //!< subtextures transform V

	glm::vec2 SubTexture::transformUV(glm::vec2 UV)
	{
		return m_UVStart + ((m_UVEnd - m_UVStart) * UV); //!< returns UV
	} //!< subtextures transform UV
}