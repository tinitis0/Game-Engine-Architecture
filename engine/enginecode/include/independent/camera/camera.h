/*! \file camera.h */
#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "events/events.h"

namespace Engine
{
	/** \class Camera
	* Base camera class
	*/
	class Camera
	{
	public:
		glm::mat4 view; //!<  camera view
		glm::mat4 projection;  //!<  camera projection

		void updateView(const glm::mat4& transform) //!< Updates view by taking in transform
		{
			view = glm::inverse(transform); //!< Updates view by taking in transform
		}


	};

	/** \class CameraController
	* Controls the camera inputs/movements
	*/

	class CameraController
	{
	public:
		Camera& getCamera() { return m_camera; } //!< gets the camera that is used
		virtual void onUpdate(float t) {}; //!< changes things on update
		virtual void onEvent(Event& e) {}; //!< changes things when event is called
	protected:
		Camera m_camera; //!< camera reference
		glm::vec3 m_pos = { 0.f, 0.f, 0.f }; //!< position

	};
}
