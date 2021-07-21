/*! \file 2DRenderer.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "rendering/2DRenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include "systems/logs.h"

namespace Engine
{
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr; //!< shared pointer to 2D renderer

	void Renderer2D::init()
	{
		s_data.reset(new InternalData); //!<resets the internal data
		unsigned char whitePx[4] = { 255, 255, 255, 255 }; //!< sets the white pixels
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePx)); //!< resets the texture create function 
			
		s_data->defaultTint = { 1.f,1.f,1.f,1.f }; //!< gets default tint from data 
		s_data->model = glm::mat4(1.0f); //!< gets model from data 

		s_data->shader.reset(Shaders::create("./assets/shaders/quad1.glsl")); //!< resets the shader create function which takes in shader file path

		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f,  0.5f, 0.f, 1.f,
			 0.5f,  0.5f, 1.f, 1.f,
			 0.5f, -0.5f, 1.f, 0.f,
		}; //!< sets the indicies as float

		uint32_t indices[4] = { 0,1,2,3 }; //!< sets the indicies as uint32_t

		std::shared_ptr<VertexBuffer> VBO; //!< shared pointer to vertex Buffer
		std::shared_ptr<IndexBuffer> IBO; //!< shared pointer to index Buffer

		s_data->VAO.reset(VertexArray::create()); //!< reset 2D renderer, Vertex array create function
		VBO.reset(VertexBuffer::create(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 }))); //!< reset vertex buffer create function in 2D renderer
		IBO.reset(IndexBuffer::create(indices, 4)); //!< reset index buffer create function in 2D renderer
		s_data->VAO->addVertexBuffer(VBO);  //!< add vertex buffer data to 2D renderer 
		s_data->VAO->setIndexBuffer(IBO); //!< set  index buffer data to 2D renderer 

		//FilePath to the font
		const char * filepath = "./assets/fonts/arial.ttf"; //!< file path for font

		//Set the dim of the glyph buffer
		s_data->glyphBufferDims = { 256,256 }; //!< set the glyph buffer dimentions
		s_data->glyphBufferSize = s_data->glyphBufferDims.x * s_data->glyphBufferDims.y * 4 * sizeof(unsigned char); //!< set the glpy buffer size
		s_data->glyphBuffer.reset(static_cast<unsigned char *> (malloc(s_data->glyphBufferSize))); //!< reset the glpy buffer
				
		//init freetype
		if (FT_Init_FreeType(&s_data->ft)) Logs::error("Error: Freetype could not be initialised!"); //!< log the arror if cant load free type library
			
		//Load the font
		if (FT_New_Face(s_data->ft, filepath, 0, &s_data->fontFace)) Logs::error("Error: Freetype could not load font {0}", filepath); //!< log error if cant load the font
		
		//Set the char size
		int32_t charSize = 70; //!< Set the character size
		if (FT_Set_Pixel_Sizes(s_data->fontFace, 0, charSize)) Logs::error("Error: freetype cant set font size! {0}", charSize); //!< if cant set the size log error
		
		s_data->fontTexture.reset(Texture::create(s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, 4, nullptr)); //!< init font texture		
		//Fill the glyph Buffer
		memset(s_data->glyphBuffer.get(), 60, s_data->glyphBufferSize); //!< fills the glyph buffer with white colour		
		s_data->fontTexture->edit(0, 0, s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, s_data->glyphBuffer.get());//!< Send glyph buffer to the texture on the gpu
	} //!< initialise the renderer

	void Renderer2D::begin(const SceneWideUniforms & swu)
	{
		//bind the shader		
		glUseProgram(s_data->shader->getID()); //!< gets the ID for shader to use
		
		for (auto& dataPair : swu)
		{
			const char * nameOfUniform = dataPair.first; //!< pairs the uniform name
			ShaderDataType sdt = dataPair.second.first; //!< pairs the shader data types
			void * addressOfValue = dataPair.second.second; //!< pairs the value addres

			switch (sdt)
			{
			case ShaderDataType::Int:
				s_data->shader->uploadInt(nameOfUniform, *(int *)addressOfValue);
				break;
			case ShaderDataType::Float3:
				s_data->shader->uploadFloat3(nameOfUniform, *(glm::vec3 *)addressOfValue);
				break;
			case ShaderDataType::Float4:
				s_data->shader->uploadFloat4(nameOfUniform, *(glm::vec4 *)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				s_data->shader->uploadMat4(nameOfUniform, *(glm::mat4 *)addressOfValue);
				break;				
			} //!< switches cases for the shader data types to be used by 2D renderer
		}//!< send the scene wide uniform to the shader

		glBindVertexArray(s_data->VAO->getRenderID());//!< binds the vertex array

	}//!< begins the 2D renderer
	
	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture);  //!< submid a quad to 2D renderer
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Texture>& texture)
	{		
		Renderer2D::submit(quad, s_data->defaultTint, texture); //!< submid a quad to 2D renderer
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Texture>& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getID()); //!< binds the texture
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale); //!< scales the model
		s_data->shader->uploadInt("u_texData", 0); //!< uploads textdata as Int
		s_data->shader->uploadFloat4("u_tint", tint); //!< uploads tint as float4
		s_data->shader->uploadMat4("u_model", s_data->model); //!< uploads model as mat4
		glBindVertexArray(s_data->VAO->getRenderID()); //!< binds vertex array
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< draws the elements
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, float angle, bool degrees)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture, angle, degrees);
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);		 //!< if the quad is rotated in degrees set it to radians
		glBindTexture(GL_TEXTURE_2D, texture->getID()); //!< binds the texture
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f}), quad.m_scale); //!< scales the model and rotates it
		s_data->shader->uploadInt("u_texData", 0); //!< uploads textdata as Int
		s_data->shader->uploadFloat4("u_tint", tint); //!< uploads tint as float4
		s_data->shader->uploadMat4("u_model", s_data->model); //!< uploads model as mat4
		glBindVertexArray(s_data->VAO->getRenderID());//!< binds vertex array
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);//!< draws the elements
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(char character, const glm::vec2 & position, float & advance, const glm::vec4& tint)
	{
		//Get glyph from freetype
		if (FT_Load_Char(s_data->fontFace, character, FT_LOAD_RENDER)) Logs::error("Error: Could not load glyph for character {0}", character); //!< if glyph from free type library cant be loaded log an error
		else
		{
			//Get glyph data
			uint32_t glyphWidth = s_data->fontFace->glyph->bitmap.width; //!< get glyph Width
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows; //!< get glyph Height
			glm::vec2 glyphSize(glyphWidth, glyphHeight); //!< get glyph size
			glm::vec2 glyphBearing(s_data->fontFace->glyph->bitmap_left, -s_data->fontFace->glyph->bitmap_top); //!< get glyph bearings			
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6); //!< Calculate the advance			
			glm::vec2 glyphHalfExtents = glm::vec2(s_data->fontTexture->getWidthf() * 0.5f, s_data->fontTexture->getHeightf() * 0.5f); //!< calculate glyph half extents
			glm::vec2 glyphCentre = (position + glyphBearing) + glyphHalfExtents; //!< calculate glyph centre
			Quad quad = Quad::createCentreHalfExtents(glyphCentre, glyphHalfExtents); //!< calculate quad for the glyph
			RendertoRGBA(s_data->fontFace->glyph->bitmap.buffer, glyphWidth, glyphHeight); //!< render to RGBA
			s_data->fontTexture->edit(0, 0, s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, s_data->glyphBuffer.get()); //!< Sets the data for the quad			
			submit(quad, tint, s_data->fontTexture); //!< submit the quad
		}//!< load the glyph from free type library
	}//!< submid a quad to 2D renderer

	void Renderer2D::submit(const char * text, const glm::vec2 & position, const glm::vec4& tint)
	{
		uint32_t len = strlen(text);//!< set the lenght of the string for the text
		float advance = 0.f, x = position.x; //!< get the position of the advance
		for (int32_t i = 0; i < len; i++)
		{
			submit(text[i], {x, position.y }, advance, tint); //!< submit the quad 
			x += advance; //!< add the advance to quad
		}//!< calculate the text
	}//!< submid a quad to 2D renderer
	
	void Renderer2D::end()
	{
	} //!< end the 2D Renderer

	void Renderer2D::RendertoRGBA(unsigned char * Rbuffer, uint32_t width, uint32_t height)
	{		
		memset(s_data->glyphBuffer.get(), 0, s_data->glyphBufferSize);
		unsigned char * pWalker = s_data->glyphBuffer.get(); //get the glyph buffer and set it to pWalker
		for (int32_t i = 0; i < height; i++)
		{
			for (int32_t j = 0; j < width; j++)
			{
				*pWalker = 255;  pWalker++; // Go to G
				*pWalker = 255;  pWalker++; // Go to B
				*pWalker = 255;  pWalker++; // Go to A
				*pWalker = *Rbuffer; // set alpha chanel
				pWalker++; // Go to R of the next pixel
				Rbuffer++; // Go to next monochrome pixel
			}//!< calculate the pWalker
			pWalker += (s_data->glyphBufferDims.x - width) * 4; //!< add buffer dimentions to calculated pWalker
		}		
	}//!< render to RGBA

	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result; //!< set the quad to be result
		result.m_translate = glm::vec3(centre, 0.f); //!<translate the result by centre
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f);//!< scale the results by half extents
		return result; //!< return results
	} //!< create centre half extents for quads


}