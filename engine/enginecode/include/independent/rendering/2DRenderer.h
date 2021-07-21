/*! \file 2DRenderer.h */

#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "shaderDataType.h"
#include "rendering/shaders.h"
#include "rendering/vertexArrays.h"
#include "rendering/texture.h"
#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine
{	
	using SceneWideUniforms = std::unordered_map<const char *, std::pair<ShaderDataType, void*>>; //!< use scene wide uniforms, by taking in shaderdatatype

	/**	\class Quad
	* Render quads 
	*/
	class Quad
	{
	public:
		Quad() = default; //!< sets Quad to default
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents); //!< constructor with parameters
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D; //!< gives access to Render2D private variables
	};	

	/**	\class Renderer2D
	* Renders in 2D
	*/
	class Renderer2D
	{
	public:
		static void init(); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begind a 2D Scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture); //!< render a textured quad		
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture); //!< render a tinted and textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< render a tinted quad thats rotated
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< render a textured quad thats rotated
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false); //!< render a tinted and textured quad thats rotated
		static void submit(char character, const glm::vec2& position, float& advance, const glm::vec4& tint); //!< Render a single character with a tint
		static void submit(const char * text, const glm::vec2& position, const glm::vec4& tint); //!< Render a single character with a tint
   		static void end(); //!< ends the renderer

	private:
		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture; //!< shared pointer to Texture
			glm::vec4 defaultTint; //!< default tint
			std::shared_ptr<Shaders> shader;//!< shared pointer to shaders
			std::shared_ptr<VertexArray> VAO;//!< shared pointer to vertex arrays
			glm::mat4 model; //!< set model
			FT_Library ft; //!< font library
			FT_Face fontFace; //!< font face
			std::shared_ptr<Texture> fontTexture; //!<font texture
			glm::ivec2 glyphBufferDims; //!< glyph buffer dims
			uint32_t glyphBufferSize; //!< glyph buffer size
			std::shared_ptr<unsigned char> glyphBuffer; //!< shared pointer of unsigned character to glyphBuffer
		};

		static std::shared_ptr<InternalData> s_data; //!< pointer to internal data
		static void RendertoRGBA(unsigned char * Rbuffer, uint32_t width, uint32_t height); //!<  render to RGBA
	};	
}