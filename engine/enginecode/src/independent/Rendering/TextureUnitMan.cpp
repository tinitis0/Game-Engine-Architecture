/*! \file TextureUnitManager.cpp */


#include "engine_pch.h"
#include "rendering/TextureUnitMan.h"

namespace Engine 
{
	void TextureUnitMan::clear()
	{
		m_head = 0; //!< sets the head to 0
		m_tail = 0; //!< sets the tail to 0
		m_full = false; //!< sets full to be false
		std::fill(m_buffer.begin(), m_buffer.end(), 0xFFFFFFFF); //!< fill the texture unit manager
	} //!< clear the texture unit manager
	bool TextureUnitMan::getUnit(uint32_t textureID, uint32_t textureUnit)
	{
		//is the texture bound?
		for (int i = m_tail; i < m_head; i++)
		{
			if (m_buffer.at(i) == textureID)
			{
				textureUnit = i;
				return false;
			}
		} //!< calculate if the texture  is bound
		//Testure unit is not bound
		//Is there soace un the buffer?
		//if there is no space then clear it
		if (m_full)
		{
			clear();
		} //!< clears if its full
		// puts texture in the buffer
		m_buffer.at(m_head) = textureID;  //!< puts texture in the buffer head
		textureUnit = m_head;  //!< puts texture in the buffer
		m_head = (++m_head) % m_capacity; //!< adds one to head and mods it
		if (m_head == m_tail) m_full = true; //!< makes sure that fullnes is updated appropriatly		
		return true; //!< return true
	} //!< get unit from texture unit manager
}