#include "handlerTests.h"
//Window Events
TEST(EventHandlerTests, onCLose) 
{	
	MockApplication app;
	Engine::WindowCloseEvent e;

	bool handledBefore = e.ishandled();
	auto& onCloseFunctionDefault = app.m_handler.getOnCloseCallback();
	onCloseFunctionDefault(e);
	bool handledDefault = e.ishandled();
	app.setCloseCallback();
	auto& onCloseFunction = app.m_handler.getOnCloseCallback();
	onCloseFunction(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onResize)
{
	MockApplication app;
	Engine::WindowResizeEvent e(500, 500);

	bool handledBefore = e.ishandled();
	auto& onResizeDefault = app.m_handler.getOnResizeCallback();
	onResizeDefault(e);
	bool handledDefault = e.ishandled();
	app.setResizeCallback();
	auto& onResizeFunction = app.m_handler.getOnResizeCallback();
	onResizeFunction(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onFocus)
{
	MockApplication app;
	Engine::WindowFocusEvent e;

	bool handledBefore = e.ishandled();
	auto& onFocusDefault = app.m_handler.getOnFocusCallback();
	onFocusDefault(e);
	bool handledDefault = e.ishandled();
	app.setFocusCallback();
	auto& onFocusFunction = app.m_handler.getOnFocusCallback();
	onFocusDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onLostFocus)
{
	MockApplication app;
	Engine::WindowLostFocusEvent e;

	bool handledBefore = e.ishandled();
	auto& onLostFocusDefault = app.m_handler.getOnLoseFocusCallback();
	onLostFocusDefault(e);
	bool handledDefault = e.ishandled();
	app.setLostFocusCallback();
	auto& onLostFocusFunction = app.m_handler.getOnLoseFocusCallback();
	onLostFocusDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onWindowMoved)
{
	MockApplication app;
	Engine::WindowMovedEvent e(200, 200);

	bool handledBefore = e.ishandled();
	auto& onWindowMovedDefault = app.m_handler.getOnWindowMovedCallback();
	onWindowMovedDefault(e);
	bool handledDefault = e.ishandled();
	app.setWindowMovedCallback();
	auto& onWindowMovedFunction = app.m_handler.getOnWindowMovedCallback();
	onWindowMovedDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
//Keyboard events
TEST(EventHandlerTests, onKeyPressed)
{
	MockApplication app;
	Engine::KeyPressedEvent e(1, 1);

	bool handledBefore = e.ishandled();
	auto& onKeyPressedDefault = app.m_handler.getOnKeyPressCallback();
	onKeyPressedDefault(e);
	bool handledDefault = e.ishandled();
	app.setKeyPressedCallback();
	auto& onKeyPressedFunction = app.m_handler.getOnKeyPressCallback();
	onKeyPressedDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onKeyRelease)
{
	MockApplication app;
	Engine::KeyReleasedEvent e(1);

	bool handledBefore = e.ishandled();
	auto& onKeyReleaseDefault = app.m_handler.getOnKeyReleaseCallback();
	onKeyReleaseDefault(e);
	bool handledDefault = e.ishandled();
	app.setKeyReleasedCallback();
	auto& onKeyReleaseFunction = app.m_handler.getOnKeyReleaseCallback();
	onKeyReleaseDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onKeyTyped)
{
	MockApplication app;
	Engine::KeyTypedEvent e(1);

	bool handledBefore = e.ishandled();
	auto& onKeyTypedDefault = app.m_handler.getOnKeyTypedeCallback();
	onKeyTypedDefault(e);
	bool handledDefault = e.ishandled();
	app.setKeyTypedCallback();
	auto& onKeyTypedFunction = app.m_handler.getOnKeyTypedeCallback();
	onKeyTypedDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
//Mouse Events
TEST(EventHandlerTests, onMouseButtonPressed)
{
	MockApplication app;
	Engine::MouseButtonPressedEvent e(1);

	bool handledBefore = e.ishandled();
	auto& onMouseButtonPressedDefault = app.m_handler.getOnMouseDownCallback();
	onMouseButtonPressedDefault(e);
	bool handledDefault = e.ishandled();
	app.setMouseButtonPressedCallback();
	auto& onMouseButtonPressedFunction = app.m_handler.getOnMouseDownCallback();
	onMouseButtonPressedDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onMouseButtonRelease)
{
	MockApplication app;
	Engine::MouseButtonReleasedEvent e(1);

	bool handledBefore = e.ishandled();
	auto& onMouseButtonReleaseDefault = app.m_handler.getOnMouseUpCallback();
	onMouseButtonReleaseDefault(e);
	bool handledDefault = e.ishandled();
	app.setMouseButtonReleasedCallback();
	auto& onKeyReleaseFunction = app.m_handler.getOnMouseUpCallback();
	onMouseButtonReleaseDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onMouseMoved)
{
	MockApplication app;
	Engine::MouseMovedEvent e(30, 30);

	bool handledBefore = e.ishandled();
	auto& onMouseMovedDefault = app.m_handler.getOnMouseMoveCallback();
	onMouseMovedDefault(e);
	bool handledDefault = e.ishandled();
	app.setMouseMovedCallback();
	auto& onMouseMovedFunction = app.m_handler.getOnMouseMoveCallback();
	onMouseMovedDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}
TEST(EventHandlerTests, onMouseScroll)
{
	MockApplication app;
	Engine::MouseScrollEvent e(30, 30);

	bool handledBefore = e.ishandled();
	auto& onMouseScrollDefault = app.m_handler.getOnMouseScrollCallback();
	onMouseScrollDefault(e);
	bool handledDefault = e.ishandled();
	app.setMouseScrollCallback();
	auto& onMouseScrollFunction = app.m_handler.getOnMouseScrollCallback();
	onMouseScrollDefault(e);
	bool handledAfter = e.ishandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}