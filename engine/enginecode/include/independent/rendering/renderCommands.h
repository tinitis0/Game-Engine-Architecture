/*! \file renderCommands.h */
#pragma once

#include<functional>

namespace Engine
{
	class RenderCommon;
	/** \class RenderCommand
	* this class sets renders commands for 2D renderer
	*/
	class RenderCommand
	{
	public:
		enum class Commands { clearDepthBuffer, clearColourBuffer, clearColourandDepthBuffer, setClearColour }; //!< command list of all commands used by renderer
	private:
		std::function<void(void)> m_action; //!< Action of the render command
		friend class RenderCommandFactory; //!< Gives access to private of render comand factory 
		friend class RenderCommon; //!< Gives access to private of render common
	};

	/** \class RenderCommandFactory
	* issues commands to renderer
	*/
	class RenderCommandFactory
	{
	public:
		template<typename ... Args> static RenderCommand * createCommand(RenderCommand::Commands command, Args&& ...args)
		{
			RenderCommand * result = new RenderCommand; //!< pointer for results

			switch (command)
			{			
			case RenderCommand::Commands::clearColourandDepthBuffer:
				result->m_action = getClearColourAndDepthBufferCommand(); // !< gets the clear command
				return result;	 //!< returns results
			case RenderCommand::Commands::setClearColour:
				float r, g, b, a; //!< sets the floats
				auto argTuple = std::make_tuple(args ...); //!< takes parameter pack and turns it into tuple
				
				getValue<float, 0>(r, argTuple); //!< get value for Red
				getValue<float, 1>(g, argTuple); //!< get value for Green
				getValue<float, 2>(b, argTuple); //!< get value for Blue
				getValue<float, 3>(a, argTuple); //!< get value for Alpha

				result->m_action = getSetClearColourCommand(r,g,b,a); //!< gets the clear command
				return result; //!< returns results
			}//!< switch statment which chooses which render command to issue
		}
		private:
			static std::function<void(void)> getClearColourAndDepthBufferCommand(); //!< get clear Colour And Depth Buffer Command
			static std::function<void(void)> getSetClearColourCommand(float r, float g, float b, float a); //!<  get Set Clear Colour Command
			static std::function<void(void)> getClearColourCommand(float r, float g, float b, float a); //!<  get Clear Colour Command
			static std::function<void(void)> getClearDepthCommand(); //!<  get Clear Colour Command

			template <typename A, size_t I, typename... Ts> //!< template
			typename std::enable_if<I >= sizeof...(Ts), void>::type
			static getValue(A&result, std::tuple<Ts...> tup)
			{

			} //!< if index number is greater than or equal tuple size dont do anything
			template <typename A, size_t I, typename... Ts> //!< template
			typename std::enable_if<I < sizeof...(Ts), void>::type 
			static getValue(A& result, std::tuple<Ts...> tup)
			{
				result = std::get<I>(tup); //!< get the Ith thing in the tupel
			} //!< gets the value for A

	};

	/** \class RenderCommon
	* sets the action command which is used by all render commands
	*/
	class RenderCommon
	{
	public:
		static void actionCommand(std::shared_ptr<RenderCommand>& command) { command->m_action(); } //!< action command which executes the render command
	};
}