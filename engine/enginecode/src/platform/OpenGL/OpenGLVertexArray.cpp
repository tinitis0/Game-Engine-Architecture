/*! \file OpenGLVertexArray.cpp */

#include "engine_pch.h"
#include<glad/glad.h>
#include"platform//OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	namespace SDT
	{
		static GLenum toGLType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Int: return GL_INT; //!< shader data type Int
			case ShaderDataType::Float: return GL_FLOAT; //!< shader data type float
			case ShaderDataType::Float2: return GL_FLOAT; //!< shader data type float2
			case ShaderDataType::Float3: return GL_FLOAT;  //!< shader data type float3
			case ShaderDataType::Float4: return GL_FLOAT;//!< shader data type float4
			case ShaderDataType::Mat4: return GL_FLOAT; //!< shader data type mat4
			default: return GL_INVALID_ENUM; //!< default returns invalid enum
			}
		} //!< shader data type to OpenGL type
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID); //!< create vertex arrays
		glBindVertexArray(m_OpenGL_ID); //!< bind vertex arrays
	} //!< default constructor

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID); //!< delete vertex arrays
	} //!< deconstructor

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		m_vertexBuffer.push_back(vertexBuffer); //!< gets vertex buffer		
		glBindVertexArray(m_OpenGL_ID); //!< binds vertex Array
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRenderID()); //!< binds buffer with vertex buffer
		const auto& layout = vertexBuffer->getLayout(); //!< auto layout to be vertex buffer get layout
		for (const auto& element : layout)
		{			
			uint32_t normalised = GL_FALSE; //!< normalised set to false
			if (element.m_normalised) { normalised = GL_TRUE; } //!< if element normalised then set normalised to true
			glEnableVertexAttribArray(m_attributeIndex); //!< enable vertex attribute array
			glVertexAttribPointer(m_attributeIndex, SDT::componentCount(element.m_datatype), SDT::toGLType(element.m_datatype), normalised, layout.getStride(), (void*)element.m_offset);  //!< vertex attribute pointer
			m_attributeIndex++;	//!< add 1 to attribute index
		}
	}//!< add vertex buffer

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer;
	} //!< set index buffer in OpenGL Vertex Array
}