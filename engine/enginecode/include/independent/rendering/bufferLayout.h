/*! \file bufferLayout.h */
#pragma once

#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/** \class  VertexBufferElement 
	* A class which holds data about a single element in a Vertex buffer layout	
	*/
	class  VertexBufferElement
	{
	public:
		ShaderDataType m_datatype; //!< get element data type
		uint32_t m_size; //!< element size
		uint32_t m_offset;//!< element offset
		bool m_normalised;  //!<bool to check if its normalised?
		VertexBufferElement() {} //!< Default constructor
		VertexBufferElement(ShaderDataType dataType, bool normalised = false) :
			m_datatype(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{}  //!< Constructor with parameters		
	};

	/** \class  UniformBufferElement
	* A class which holds data about a single element in a uniform Buffer layout
	*/
	class  UniformBufferElement
	{
	public:
		const char * m_name; //!< name if the uniform buffer
		ShaderDataType m_datatype; //!< get element data type
		uint32_t m_size; //!< element size
		uint32_t m_offset;//!< element offset		
		UniformBufferElement() {} //!< Default constructor
		UniformBufferElement(const char * name, ShaderDataType dataType) :
			m_name(name),
			m_datatype(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0)			
		{}  //!< Constructor with parameters
	}; 

	/** \class bufferLayout
	* Abstraction of the notion of a buffer layout
	*/
	template <class G> //!< sets a template for the class
	class  BufferLayout
	{
	private:
		std::vector<G> m_elements; //!< Buffer elements
		uint32_t m_stride; //!<Width is bytes of the buffer line
		void calculateStrideAndOffset(); //!<Calculate stride and offset based on elements
	public: 
		BufferLayout<G>() {};  //!< Default constructor
		BufferLayout<G>(const std::initializer_list <G>& element) : m_elements(element) { calculateStrideAndOffset(); } // !< Constructor which takes elements
		inline uint32_t getStride() const { return m_stride; } //!< gets element stride
		void addElement(G element); //!<  add elements to buffer layout
		inline typename std::vector<G>::iterator begin() { return m_elements.begin(); } //!< begin the buffer element
		inline typename std::vector<G>::iterator end() { return m_elements.end(); } //!< End the buffer element
		inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); } //!< begin the buffer element
		inline typename std::vector<G>::const_iterator end() const { return m_elements.end(); } //!< End the buffer element		
	};
	template <class G> //!< sets a template for the class
	void BufferLayout<G>::addElement(G element) //!< Adds element to buffer Layout
	{
		m_elements.push_back(element); //!< gets the element
		calculateStrideAndOffset(); //!< calculates stride and offset for element
	}
	template <class G> //!< sets a template for the class
	void BufferLayout<G>::calculateStrideAndOffset() //!< calculate the element stride and offset
	{
		uint32_t l_offset = 0; //!< sets the offset to be 0 by default
		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		} //!< sets the element offset
		m_stride = l_offset; //!< ofset is equal to stride
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>; //!< Creates vertex buffer layout, by taking in vertex buffer element
	using UniformBufferLayout = BufferLayout<UniformBufferElement>; //!< Creates uniform buffer layout, by taking in uniform buffer element
}
