/*! \file renderAPI.h */
#pragma once

namespace Engine
{
	/** \class RenderAPI
	* Rendering API's to choose from
	*/
	class RenderAPI
	{
	public: 
		enum class API {None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3}; //!< enum class that selects the renderer to use
		inline static API getAPI() { return s_API; } //!< gets the current API
	private:
		static API s_API; //!< Current API
	};

	
}
 