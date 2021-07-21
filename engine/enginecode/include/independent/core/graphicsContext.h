/*! \file graphicsContext.h
*/
#pragma once

namespace
{

	/** \class GraphicsContext
	* graphical content in the application
	*/
	class GraphicsContext
	{
	public:
		virtual void init() = 0; //!< initialise the graphics context for the given window API
		virtual void swapBuffers() = 0; //!< Swaps the front and back buffer
	};
}