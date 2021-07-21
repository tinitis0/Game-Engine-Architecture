/* \file shaders.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine
{
	/** \class Shaders
	* API agnostic Shaders
	*/
	class Shaders
	{
	public:
		virtual ~Shaders() = default; //!<Deconstructor
		virtual inline uint32_t getID() const = 0; //!< Gets the int ID and returns render ID		
		static Shaders* create(const char* filepath); //!< creates the Shaders by taking in filepath
		static Shaders* create(const char* vertexFilepath, const char* fragmentFilepath);  //!< creates the Shaders by takingin the parameters		
		virtual void uploadInt(const char* name, int value) = 0; //!< upload sample2D
		virtual void uploadFloat(const char* name, float value) = 0; //!< upload Float
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0; //!< upload Float2
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0; //!< upload Float3
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0; //!< upload Float4
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0; //!< upload matricies4		
	};
}