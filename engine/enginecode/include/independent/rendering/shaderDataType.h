/*! \file shaderDataType.h */
#pragma once

#include <cstdint>

namespace Engine
{
	/* \ enum class ShaderDataType
	* Size and count of shader data type
	*/
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int
	}; //!< shader data types to chose from

	namespace SDT
	{
		static uint32_t size(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float: return 4; //!< gives return for shader data type float
			case ShaderDataType::Float2: return 4 * 2;//!< gives return for shader data type float2
			case ShaderDataType::Float3: return 4 * 3;//!< gives return for shader data type float3
			case ShaderDataType::Float4: return 4 * 4;//!< gives return for shader data type float4
			case ShaderDataType::Mat3: return 4 * 3 * 3;//!< gives return for shader data type mat3
			case ShaderDataType::Mat4: return 4 * 4 * 4;//!< gives return for shader data type mat4
			default: return 0; //!< sets the default return to 0
			}
		} //!< size which takes in shader data type

		static uint32_t componentCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float: return 1;  //!< gives return for shader data type float
			case ShaderDataType::Float2: return 2; //!< gives return for shader data type float2
			case ShaderDataType::Float3: return 3; //!< gives return for shader data type float3
			case ShaderDataType::Float4: return 4; //!< gives return for shader data type float4
			case ShaderDataType::Mat3: return 4 * 3; //!< gives return for shader data type mat3
			case ShaderDataType::Mat4: return 4 * 4; //!< gives return for shader data type mat4
			default: return 0; //!< sets the default return to 0
			}
		} //!< component count which takes in shader data type 


	}

	static uint32_t std104alignment(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return 4; //!< gives return for shader data type float
		case ShaderDataType::Float2: return 4 * 2; //!< gives return for shader data type float2
		case ShaderDataType::Float3: return 4 * 4; //!< gives return for shader data type float3
		case ShaderDataType::Float4: return 4 * 4; //!< gives return for shader data type float4
		case ShaderDataType::Mat3: return 4 * 3 * 3; //!< gives return for shader data type mat3
		case ShaderDataType::Mat4: return 4 * 4 * 4; //!< gives return for shader data type mat4
		default: return 0;//!< sets the default return to 0
		}
	}//!< std104alignment which takes in shader data type 
}
