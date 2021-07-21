/*! \file application.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif  // DEBUG NG_PLATFORM_WINDOWS
#ifdef NG_PLATFORM_WINDOWS
#include "platform/windows/winTimer.h"
#endif // DEBUG NG_PLATFORM_WINDOWS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/indexBuffer.h"
#include "Rendering/vertexBuffer.h"
#include "Rendering/texture.h"
#include "Rendering/shaders.h"
#include "Rendering/vertexArrays.h"
#include "Rendering/subTexture.h"
#include "Rendering/UniformBuffer.h" 
#include "rendering/TextureUnitMan.h"
#include "rendering/2DRenderer.h" 
#include "camera/orthographic2DCamera.h"
#include "rendering/renderCommands.h"

namespace Engine 
{	
	Application* Application::s_instance = nullptr;//!< Set static vars

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		//start systems

		
		m_logSystem.reset(new Logs);//!< reset the log system
		m_logSystem->start();//!< start log system

		// start the timer
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer); //!< reset the window timer
#else 
		m_timer.reset(new ChronoTimer); //!< reset the chrono timer
#endif
		m_timer->start(); //!< start the timer

		//start the window system
#ifdef NG_PLATFORM_WINDOWS
		m_windowSystem.reset(new GLFWSystem); //!< reset window system
#endif // DEBUG NG_PLATFORM_WINDOWS
		m_windowSystem->start(); //!< start the window system

		WindowProperties props("My Game Engine", 1024, 800); //!<set window properties
		m_window.reset(Window::create(props)); //!< reset window create with properties


		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1)); //!< get set on close call back event
		m_window->getEventHandler().setOnResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1)); //!< get set on resize call back event
		m_window->getEventHandler().setOnFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1)); //!< get set on focus call back event
		m_window->getEventHandler().setOnLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1)); //!< get set on lose focus call back event
		m_window->getEventHandler().setOnWindowMovedCallback(std::bind(&Application::onWindowMoved, this, std::placeholders::_1)); //!< get set on window moved call back event

		m_window->getEventHandler().setOnKeyPressCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1)); //!< get set on on key press call back event
		m_window->getEventHandler().setOnKeyReleaseCallback(std::bind(&Application::onKeyReleased, this, std::placeholders::_1)); //!< get set on  on key release call back event

		m_window->getEventHandler().setOnMouseDownCallback(std::bind(&Application::onMouseDown, this, std::placeholders::_1)); //!< get set on mouse down call back event
		m_window->getEventHandler().setOnMouseUpCallback(std::bind(&Application::onMouseUp, this, std::placeholders::_1)); //!< get set on  mouse up call back event
		m_window->getEventHandler().setOnMouseScrollCallback(std::bind(&Application::onScroll, this, std::placeholders::_1)); //!< get set on mouse scroll call back event
		m_window->getEventHandler().setOnMouseMovedCallback(std::bind(&Application::onMouseMoved, this, std::placeholders::_1)); //!< get set on mouse moved call back event

		InputPoller::setNativeWin(m_window->getNativeWindow()); //!< set the native window
		m_timer->reset(); //!< reset the timer
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		e.handle(true);
		m_running = false;
		Logs::info("Window Closed");
		return e.ishandled();
	} //!< on close event

	bool Application::onResize(WindowResizeEvent & e)
	{
		e.handle(true);
		auto& size = e.getSize();
		Logs::info("Window Resize event: ({0}, {1})", size.x, size.y);
		return e.ishandled();
	} //!< on resize event

	bool Application::onFocus(WindowFocusEvent & e) // needs to be checked
	{
		e.handle(true);
		Logs::info("Gained focus");
		return e.ishandled();
	} //!< on onfocus event

	bool Application::onLostFocus(WindowLostFocusEvent & e) // needs to be checked
	{
		e.handle(true);
		Logs::info("Lost focus");
		return e.ishandled();
	}//!< on lose focus event

	bool Application::onWindowMoved(WindowMovedEvent & e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		Logs::info("Window Moved Event: ({0}, {1})", pos.x, pos.y);
		return e.ishandled();
	}//!< on window moved event
	   	 

	bool Application::onKeyPressed(KeyPressedEvent & e)
	{
		e.handle(true);
		Logs::info("Key Press event: key: {0}, repeat: {1}", e.getKeyCode(), e.getAmountPressed());
		if (e.getKeyCode() == NG_KEY_SPACE) Logs::error("SPACEBAR Pressed");
		return e.ishandled();
	} //!< on key pressed event

	bool Application::onKeyReleased(KeyReleasedEvent & e)
	{
		e.handle(true);
		Logs::info("Key Released event: key:{0}",e.getKeyCode());
		if (e.getKeyCode() == NG_KEY_UP) Logs::error("UP Released");
		return e.ishandled();
	} //!< on key released event


	bool Application::onMouseDown(MouseButtonPressedEvent & e)
	{
		e.handle(true);
		Logs::info("Mouse Pressed event: button:{0}", e.getPressedButton());
		return e.ishandled();
	} //!< on mouse down event

	bool Application::onMouseUp(MouseButtonReleasedEvent & e)
	{
		e.handle(true);
		Logs::info("Mouse Released event: button:{0}", e.getreleasedButton());
		return e.ishandled();
	} //!< on mouse up event

	bool Application::onScroll(MouseScrollEvent & e)
	{
		e.handle(true);
		Logs::info("Mouse Scroll event: {0}",  e.getYOffsetPos());
		return e.ishandled();
	}//!< on scroll event

	bool Application::onMouseMoved(MouseMovedEvent & e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		Logs::info("Mouse Moved event: ({0}, {1})", pos.x, pos.y);
		return e.ishandled();
	}//!< on mouse moved event

	Application::~Application()
	{
		//Stop systems		
		m_logSystem->stop();	//!<stop logger	
		m_windowSystem->stop(); //!< stop windows system
	} //!< deconstructor
	
	void Application::run()
	{
#pragma region TEXTURES
		std::shared_ptr<Texture> letterTexture;
		letterTexture.reset(Texture::create("assets/textures/letterCube.png")); //!< gets the texture from file location
		std::shared_ptr<Texture> numberTexture;
		numberTexture.reset(Texture::create("assets/textures/numberCube.png")); //!< gets the texture from file location

		//letterTexture.reset(new OpenGLTexture("assets/textures/letterAndNumberCube.png")); //!< using sub textures
		//SubTexture letterCube(letterTexture, { 0.f, 0.f, }, { 1.0f, 0.5f });
		//SubTexture numberCube(numberTexture, { 0.f, 0.5f, }, { 1.0f, 1.0f });

#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,	0.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.5f,
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,	0.33f, 0.5f,
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.f,

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.5f,
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.f,
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33,  0.f,

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  1.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  0.66f, 0.f,
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  0.66f, 0.5f,
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  1.0f,  0.5f,

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.f,   0.5f,
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.f,   1.0f,
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.33f, 1.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.3f,  0.5f,

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 0.5f,
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 0.5f,
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 1.0f,
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 1.0f,

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  0.5f,
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 0.5f,
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 1.0f
		};
		/*  The subtextures for the text and letter cubes
		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,	letterCube.transformU(0.f),   letterCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.f),   letterCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,	letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.f),

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.66f), letterCube.transformV(0.f),
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.33),  letterCube.transformV(0.f),

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  letterCube.transformU(1.f),   letterCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(0.5f),

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  letterCube.transformU(0.f),   letterCube.transformV(0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  letterCube.transformU(0.f),   letterCube.transformV(1.0f),
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  letterCube.transformU(0.33f), letterCube.transformV(1.0f),
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  letterCube.transformU(0.3f),  letterCube.transformV(0.5f),

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  letterCube.transformU(0.33f), letterCube.transformV(1.0f),
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(1.0f),

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(1.0f)
		};
		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,	numberCube.transformU(0.f),   numberCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  numberCube.transformU(0.f),   numberCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,	numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  numberCube.transformU(0.33f), numberCube.transformV(0.f),

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.66f), numberCube.transformV(0.f),
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.33),  numberCube.transformV(0.f),

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  numberCube.transformU(1.f),   numberCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(0.5f),

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numberCube.transformU(0.f),   numberCube.transformV(0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numberCube.transformU(0.f),   numberCube.transformV(1.0f),
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(1.0f),
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numberCube.transformU(0.3f),  numberCube.transformV(0.5f),

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(1.0f),
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(1.0f),

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(1.0f)
		};
		*/
		float pyramidVertices[6 * 16] = {
			//	 <------ Pos ------>  <--- colour ---> 
				-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
				 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
				-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

				-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

				-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
				 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;


		cubeVAO.reset(VertexArray::create());
		VertexBufferLayout cubeBL = { ShaderDataType::Float3,ShaderDataType::Float3, ShaderDataType::Float2 };

		cubeVBO.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));

		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(VertexArray::create());

		VertexBufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3 };
		pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), pyramidBL));
		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);


#pragma endregion


#pragma region SHADERS
		std::shared_ptr<Shaders> flatColourShader; //!< shared pointer to flat colour shader
		flatColourShader.reset(Shaders::create("./assets/shaders/flatColour.glsl")); //!< resets and creates new colour shader with filepath

		std::shared_ptr<Shaders> TPShader; //!< shared pointer to textured phong shader
		TPShader.reset(Shaders::create("./assets/shaders/texturedPhong.glsl")); //!< resets and creates new texture phong shader with filepath
#pragma endregion 

#pragma endregion

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);	//!< camera view position, camera views streight down Z axis and Upwards is set upwards (as default)
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f); //!<field of view, aspect ratio
		FreeOrthographic2DCamera Cam2D(0, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0); //!< setsthe Free orthagraphic 2D camera as Cam2D		

		//Camera UBO
		uint32_t blockNumber = 0; //!< sets the block number
		UniformBufferLayout camLayout = { { "u_projection", ShaderDataType::Mat4}, { "u_view", ShaderDataType::Mat4} }; //!< camera layout from uniform buffer
		std::shared_ptr<UniformBuffer> cameraUBO; //!< shared pointer to camera UBO
		cameraUBO.reset(UniformBuffer::create(camLayout)); //!< reset the camera UBO

		cameraUBO->attachShaderBlock(flatColourShader, "b_camera");	//!< attach shader to camera UBO
		cameraUBO->attachShaderBlock(TPShader, "b_camera"); //!< attach shader to camera UBO

		cameraUBO->uploadData("u_projection", glm::value_ptr(projection)); //!< upload data to camera UBO
		cameraUBO->uploadData("u_view", glm::value_ptr(view));  //!< upload data to camera UBO

		blockNumber++; //!< increase block number

		glm::vec3 lightColour(1.f, 1.f, 1.f); //!< set light colour
		glm::vec3 lightPos(1.f, 4.f, 6.f);  //!< set light position
		glm::vec3 viewPos(0.f, 0.f, 0.f);  //!< set view position

		uint32_t lightUBO; //!< set lightUBO
		uint32_t lightDataSize = sizeof(glm::vec4) * 3; //!< set the light data size

		glGenBuffers(1, &lightUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightUBO); //!< bind the light UBO buffer
		glBufferData(GL_UNIFORM_BUFFER, lightDataSize, nullptr, GL_DYNAMIC_DRAW);  //!< get the light UBO buffer data
		glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, lightUBO, 0, lightDataSize);  //!< bind the light UBO buffer range

		uint32_t blockIndex = glGetUniformBlockIndex(TPShader->getID(), "b_lights"); //!< get block index
		glUniformBlockBinding(TPShader->getID(), blockIndex, blockNumber); //!< bind the uniform block

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightPos)); //!< get sub data for uniform buffer for block
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(viewPos)); //!< get sub data for uniform buffer for block
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(lightColour)); //!< get sub data for uniform buffer for block

		glm::mat4 models[3];//!< model matrix				
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f)); //!< translate the model 
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f)); //!< translate the model 
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f)); //!< translate the model 



		SceneWideUniforms swu2D; //!< set scene wide uniforms
		swu2D["u_view"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(Cam2D.getCamera().view))); //!< set the view for scene wide uniforms
		swu2D["u_projection"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(Cam2D.getCamera().projection)));  //!< set the projection for scene wide uniforms

		Quad quads[6] =
		{
		Quad::createCentreHalfExtents({ 400.f, 200.f }, { 125.f, 50.f }),
		Quad::createCentreHalfExtents({ 400.f, 700.f }, { 75.f, 75.f }),
		Quad::createCentreHalfExtents({ 900.f, 150.f }, { 100.f, 100.f }),
		Quad::createCentreHalfExtents({ 100.f, 200.f }, { 75.f, 50.f }),
		Quad::createCentreHalfExtents({ 500.f, 600.f }, { 55.f, 25.f }),
		Quad::createCentreHalfExtents({ 300.f, 100.f }, { 50.f, 10.f })

		}; //!< set the quads with half extents

		float timestep = 0.f; //!< set the timestep

		glEnable(GL_DEPTH_TEST); //!< enable depth test
		

		TextureUnitMan uMan(32); //!< set texture unit manager
		uint32_t unit = 0; //!< set the unit to be 0

		Renderer2D::init(); //!< init the 2D renderer

		std::shared_ptr<RenderCommand> clearCommand; //!< shared pointer to render command 
		clearCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::clearColourandDepthBuffer)); //!< resets the command and renders this command
		
		{
		std::shared_ptr<RenderCommand> setClearCommand; //!< shared pointer to render command 
		setClearCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::setClearColour, 1.0f,0.4f,0.4f,1.0f)); //!< resets the command and renders this command
		RenderCommon::actionCommand(setClearCommand); //!< renders common actionCommand
		} //!< set in scope to clear up memory after set clear command goes out of scope

		float advance; //!< set advance
		while (m_running)
		{
			timestep = m_timer->getElapsedTime(); //!< set timestep to be timer
			m_timer->reset(); //!< reset the timer

			 Logs::trace("FPS {0}", 1.0f/timestep);
			 if (InputPoller::isKeyPressed(NG_KEY_W)) Logs::error("W Pressed"); //!< logs if the key W is pressed
			 if (InputPoller::isKeyPressed(NG_KEY_S)) Logs::error("S Pressed"); //!< logs if the key S is pressed
			 if (InputPoller::isKeyPressed(NG_KEY_A)) Logs::error("A Pressed"); //!< logs if the key A is pressed
			 if (InputPoller::isKeyPressed(NG_KEY_D)) Logs::error("D Pressed"); //!< logs if the key D is pressed
			 if (InputPoller::isKeyPressed(NG_KEY_Q)) Logs::error("Q Pressed"); //!< logs if the key Q is pressed
			 if (InputPoller::isKeyPressed(NG_KEY_E)) Logs::error("E Pressed"); //!< logs if the key E is pressed
			 if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_1)) Logs::error("Left Mouse Button Pressed"); //!< logs if the mouse button 1 is pressed
			 if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_2)) Logs::error("Right Mouse Button Pressed"); //!< logs if the mouse button 2 is pressed
			 //Logs::trace("Current mouse position: ({0}, {1})", InputPoller::getMouseX(), InputPoller::getMouseY()); //!< logs the trace of mouse position
			
			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(-0.2f, 1.0, 0.f)); } //!< spins the Triangle and Cubes				

			// Do frame stuff			
			RenderCommon::actionCommand(clearCommand); //!< renders common actionCommand

			glUseProgram(flatColourShader->getID()); //!< binds  the shader
			
			glBindVertexArray(pyramidVAO->getRenderID()); //!< binds  the vertex array
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->getRenderID());  //!< bounds  the shader index array

			GLuint location;

			location = glGetUniformLocation(flatColourShader->getID(), "u_model"); //!< set location for model
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(models[0])); //!< get uniform matrics for model 0

			flatColourShader->uploadMat4("u_model", models[0]); //!< upload mat4 model from flat colour shader
			flatColourShader->uploadMat4("u_view", view); //!< upload mat4 view from flat colour shader
			flatColourShader->uploadMat4("u_projection", projection); //!< upload mat4 projection from flat colour shader

			glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< draw the elements for triangles 
						
			glUseProgram(TPShader->getID()); //!< get TP shader
			glBindVertexArray(cubeVAO->getRenderID()); //!< bind vertex array for cubeVAO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getRenderID()); //!< bind buffer for cube and render ID

			glBindTexture(GL_TEXTURE_2D, letterTexture->getID()); //!< bind the letter texture to cube
			TPShader->uploadMat4("u_model", models[1]); //!< upload model as mat4
			TPShader->uploadMat4("u_view", view); //!< upload view as mat4
			TPShader->uploadMat4("u_projection", projection); //!< upload projection as mat4
			TPShader->uploadFloat3("u_lightColour", { 1.0f, 1.0f, 1.0f }); //!< upload light colour as float3
			TPShader->uploadFloat3("u_lightPos", { 1.0f, 1.0f, 1.0f }); //!< upload light position as float3
			TPShader->uploadFloat3("u_viewPos", { 1.0f, 1.0f, 1.0f }); //!< upload view position as float3
			TPShader->uploadInt("u_textData", 0);  //!< upload tex data as int
			
			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< draw elements for cube VAO		
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(models[2]));	//!< get model 2
			glBindTexture(GL_TEXTURE_2D, numberTexture->getID()); //!< bind the number texture to cube

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr); //!< draw the elements for  cube

			//glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND); 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			Renderer2D::begin(swu2D);
			Renderer2D::submit(quads[0], {0.f,0.f,1.f,1.f});
			Renderer2D::submit(quads[1], letterTexture);
			Renderer2D::submit(quads[2], { 1.f,1.f,0.f,1.f }, numberTexture);
			Renderer2D::submit(quads[3], { 1.f,0.f,1.f,0.5f }, numberTexture, 45.f, true);
			Renderer2D::submit(quads[3], { 0.f,1.f,1.f,0.5f }, numberTexture, glm::radians(-45.f));
			Renderer2D::submit(quads[4], { 1.f,0.f,0.f,1.f }, 90.f, true);
			Renderer2D::submit(quads[5], { 0.f,1.f,0.f,1.f }, numberTexture, 35.f, true);

			uint32_t x = 550.f;
			Renderer2D::submit('g', { x,550.f }, advance, { 1.f,1.f,1.f,1.f }); x += advance;  //!< renders character with 2D renderer
			Renderer2D::submit('o', { x,550.f }, advance, { 1.f,1.f,1.f,1.f }); x += advance;  //!< renders character with 2D renderer
			Renderer2D::submit(' ', { x,550.f }, advance, { 1.f,1.f,1.f,1.f }); x += advance;  //!< renders character with 2D renderer
			Renderer2D::submit('l', { x,550.f }, advance, { 1.f,1.f,1.f,1.f }); x += advance;  //!< renders character with 2D renderer
			Renderer2D::submit('o', { x,550.f }, advance, { 1.f,1.f,1.f,1.f }); x += advance;  //!< renders character with 2D renderer
			Renderer2D::submit('l', { x,550.f }, advance, { 1.f,1.f,1.f,1.f }); x += advance;  //!< renders character with 2D renderer

			Renderer2D::submit("Hello World.", { 200.f,70.f }, { 1.f,1.f,1.f,1.f }); //!< renders text with 2D renderer

			Renderer2D::end(); //!< ends the 2D renderer			

			glDisable(GL_BLEND); 

			m_window->onUpdate(timestep);
			Cam2D.onUpdate(timestep);

			swu2D["u_view"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(Cam2D.getCamera().view))); //!< sets the view for the SWU2D camera
			swu2D["u_projection"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(Cam2D.getCamera().projection))); //!< sets the view for the SWU2D camera
		}		
	}
}
