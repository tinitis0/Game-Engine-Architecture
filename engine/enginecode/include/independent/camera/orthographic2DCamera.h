/*! \file orthographic2DCamera.h */
#pragma once

#include "camera/camera.h"

namespace Engine
{
	/** \class FreeOrthographic2DCamera
	* 2D Orthographic camera for the scene
	*/
	class FreeOrthographic2DCamera : public CameraController
	{
	public:
		FreeOrthographic2DCamera(float left, float right, float top, float bottom); //!< Constructor takes in 4 floats
		virtual void onUpdate(float timestep) override; //!< updates the camera onUpdate by taking in timestep
	private:
		float m_rotation = 0.f; //!< rotation andgle of the camera
		float m_translationSpeed = 60.f; //!< translation speed of the camera
		float m_rotationSpeed = 2.f; //!< rotation speed of the camera
	};
}