/*! \file textureAtlas.cpp */

#include "engine_pch.h"
#include "rendering/textureAtlas.h"
#include "stb_image.h"

namespace Engine
{
	TextureAtlas::TextureAtlas(glm::ivec2 size, uint32_t channels, uint32_t reservedSpaces )
	{
		m_baseTexture.reset(Texture::create(size.x, size.y, channels, nullptr)); //!< alocates api agnostic texture
		m_spaces.reserve(reservedSpaces);//!< reserves spaces for texture
		m_spaces.push_back({ 0,0,static_cast<uint32_t> (size.x), static_cast<uint32_t>(size.y) }); //!< first space
	} //!< Constructor with parameters

	bool TextureAtlas::add(const char * filepath, SubTexture & result)
	{
		int32_t width, height, channels; //!< sets int to width, height and channels of texture atlas
		unsigned char * data = stbi_load(filepath,&width, &height, &channels,static_cast<int> (getChannels())); //!< loads the file and sets the parameters to get data 
		if (data) return add(width, height, channels, data, result); //!< if there is data return it
		return false; //!< if there is no data return false
	}//!< add data to texture atlas

	bool TextureAtlas::add(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data, SubTexture & result)
	{
		if (channels != getChannels()) return false; //!< Early exit as channels dont match
		for (auto iterrator = m_spaces.begin(); iterrator != m_spaces.end(); ++iterrator)
		{
			auto& space = *iterrator;
			// checks if there is space for the texture
			if (width < space.w && height < space.h)
			{
				
				m_baseTexture->edit(space.x, space.y, width, height, data);//!< texture fits! add texture data
				//set SAubtexture results 
				glm::vec2 UVStart(static_cast<float>(space.x) / m_baseTexture->getWidthf(), static_cast<float>(space.y) / m_baseTexture->getHeightf()); //!< start of the texture divided by texture width and height
				glm::vec2 UVEnd(static_cast<float>(space.x + space.w) / m_baseTexture->getWidthf(), static_cast<float>(space.y + space.h) / m_baseTexture->getHeightf()); //!< endpoint
				result = SubTexture(m_baseTexture, UVStart, UVEnd); //!< rsults for the subtexture start and end position
				//Sort out remaining spaces

				//Case 1: Texture matches space size, delete space
				if (width == space.w && height == space.h)
				{
					m_spaces.erase(iterrator);
					return true;
				}

				//Case 2: Texture widht matches space width, heights do not match - splits  the space horizontally into two
				else if (width == space.w)
				{
					space.y += height;
					space.h -= height;
					return true;
				}
				//-----------			-----------
				//|		    |			|	 	  | 
				//|	 Space	|  Becomes  |---------|
				//|			|			|  Space  |
				//-----------			-----------
				
				//Case 3: Texture height matches space height, width do not match - splits  the space vertically into two
				else if (height == space.h)
				{
					space.x += width;
					space.w -= width;
					return true;
				}
				//-----------			-----------
				//|		    |			|	 | Sp | 
				//|	 Space	|  Becomes  |	 | ac |
				//|			|			|	 | e  |
				//-----------			-----------

				//Case 4: Texture height and width do not match - splits  the space horizantally and vertically 
				else 
				{
					m_spaces.push_back({ space.x, space.y + height, width, space.h - height });
					space.x += width;
					space.w -= width;
					return true;
				}
				//-----------			-----------
				//|		    |			|	 |Sp  | 
				//|	 Space	|  Becomes  |----|ac  |
				//|			|			|Spa |e   |
				//-----------			-----------
			}
		}
		return false;
	}
}