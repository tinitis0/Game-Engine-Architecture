/*! \file orthographic2DCamera.cpp */

#include "engine_pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "events/codes.h"
#include "core/inputPoller.h"
#include "camera/orthographic2DCamera.h"

namespace Engine
{
	FreeOrthographic2DCamera::FreeOrthographic2DCamera(float left, float right, float top, float bottom)
	{
		m_camera.projection = glm::ortho(left, right, top, bottom);
		m_camera.view = glm::mat3(1.f);
	} //!< constructor with parameters

	void FreeOrthographic2DCamera::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(NG_KEY_W))
		{
			m_pos.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_pos.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		} //!< If W is pressed calculate the position
		if (InputPoller::isKeyPressed(NG_KEY_S))
		{
			m_pos.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_pos.y += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}//!< If S is pressed calculate the position
		if (InputPoller::isKeyPressed(NG_KEY_A))
		{
			m_pos.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_pos.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}//!< If A is pressed calculate the position
		if (InputPoller::isKeyPressed(NG_KEY_D))
		{
			m_pos.x += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_pos.y += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		} //!< If D is pressed calculate the position
		if (InputPoller::isKeyPressed(NG_KEY_Q))
		{
			m_rotation -= timestep * m_rotationSpeed;
			if (m_rotation > 180.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -180.0f) m_rotation += 360.0f;			
		} //!< If Q is pressed calculate the rotation
		if (InputPoller::isKeyPressed(NG_KEY_E))
		{
			m_rotation += timestep * m_rotationSpeed;
			if (m_rotation > 180.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -180.0f) m_rotation += 360.0f;
		} //!< If E is pressed calculate the rotation

		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos.y, 1.f)); //!< translation of the camera
		glm::mat4 rotate = glm::rotate(glm::mat4(1.f), m_rotation, { 0.0f, 0.0f, 1.0f }); //!< rotation of the camera
		m_camera.view = glm::inverse(translate * rotate); //!< camera view	
	} //!< on update, updates the functions
}