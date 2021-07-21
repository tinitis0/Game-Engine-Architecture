/*! \file TextureUnitManager.h */
#pragma once

#include <vector>

namespace Engine
{
	/** \class TextureUnitManager
	* manages texture units
	*/
	class TextureUnitMan
	{
	public:
		TextureUnitMan(uint32_t capacity) : m_capacity(capacity), m_buffer(capacity, 0xFFFFFFFF) {} //!< constructor which takes in  a capacity  
		inline bool full(){ return m_full; } //!< is the buffer full?
		void clear(); //!< clear and reset the buffer
		bool getUnit(uint32_t textureID, uint32_t textureUnit); //!<returns wheather or not the texture needs binding to the unit. texture unit is always set to unit
	private:
		uint32_t m_capacity; //!< Capacity of ring buffer
		std::vector<uint32_t> m_buffer; //!< Internal buffer
		bool m_full = false; //!< checks if the buffer is full or not
		uint32_t m_head = 0; //!< Head of the buffer
		uint32_t m_tail = 0;//!< tail of the buffer
	};
}