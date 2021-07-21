#include "EventTests.h"

//////////////////////////////////////////
/////////////// Window ///////////////////
//////////////////////////////////////////

TEST(EventsTests, ResizeConstructor) {
	Engine::WindowResizeEvent a(800, 600);

	int32_t width = a.getWidth();
	int32_t height = a.getHeight();
	auto size = a.getSize();
	int32_t width2 = size.x; 
	int32_t height2 = size.y;
	
	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_EQ(width, 800); //!< Checking if width is correct
	EXPECT_EQ(width2, 800); //!< Checking if size is correct
	EXPECT_EQ(height, 600); //!< Checking if height is correct
	EXPECT_EQ(height2, 600); //!< Checking if size is correct

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryWindow); //!< Checking if its in the right category
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryWindow)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::WindowResize); //!< Checking if type is the WindowResizeEvent
}

TEST(EventsTests, CloseConstructor) {
	Engine::WindowCloseEvent a;

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();	

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryWindow); //!< Checking if its in the right category
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryWindow)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::WindowClose); //!< Checking if type is the WindowCloseEvent
}

TEST(EventsTests, FocusConstructor) {
	Engine::WindowFocusEvent a;

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryWindow); //!< Checking if its in the right category
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryWindow)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::WindowFocus); //!< Checking if type is the WindowFocusEvent
}

TEST(EventsTests, LostFocusConstructor) {
	Engine::WindowLostFocusEvent a;

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryWindow); //!< Checking if its in the right category
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryWindow)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::WindowLostFocus); //!< Checking if type is the WindowLostFocusEvent
}
TEST(EventsTests, WindowMoveConstructor) {
	Engine::WindowMovedEvent a(300, 200);


	int32_t X = a.getXPosition();
	int32_t Y = a.getYPosition();
	auto Pos = a.getPos();
	int32_t NewPos = (Pos.x, Pos.y);
	

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_EQ(X, 300); //!< Checking if X pos is correct
	EXPECT_EQ(Y, 200); //!< Checking if Y pos is correct
	

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryWindow); //!< Checking if its in the right category
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryWindow)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::WindowMoved); //!< Checking if type is the WindowMoved
}

//////////////////////////////////////////
////////////// Keyboard //////////////////
//////////////////////////////////////////

TEST(EventsTests,KeyPressedConstructor) {
	Engine::KeyPressedEvent a(1,1);

	int32_t Keycode = a.getKeyCode();
	int32_t Amount = a.getAmountPressed();	

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_EQ(Keycode, Amount); //!< Checking if Key is pressed and how many times

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryKeyboard); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryKeyboard)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::KeyPressed); //!< Checking if type is the KeyPressed
}
TEST(EventsTests, KeyReleasedConstructor) {
	Engine::KeyReleasedEvent a(1);

	int32_t Keycode = a.getKeyCode();	

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_TRUE(Keycode);  //!< Checking if Key is correct keycode

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryKeyboard); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryKeyboard)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::KeyReleased); //!< Checking if type is the KeyReleased
}
TEST(EventsTests, KeyTypedConstructor) {
	Engine::KeyTypedEvent a(1);

	int32_t Keycode = a.getKeyCode();

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_TRUE(Keycode); //!< Checking if Key is correct keycode

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryKeyboard); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryKeyboard)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::KeyTyped); //!< Checking if type is the KeyTyped
}

//////////////////////////////////////////
/////////////// Mouse ////////////////////
//////////////////////////////////////////

TEST(EventsTests, MouseButtonPressedConstructor) {
	Engine::MouseButtonPressedEvent a(1);

	int32_t pressedButton = a.getPressedButton();

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_TRUE(pressedButton); //!< Checking if button is pressed 

	EXPECT_EQ (category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryMouse); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryMouse)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::MouseButtonPressed); //!< Checking if type is the MouseButtonPressed
}
TEST(EventsTests, MouseButtonReleasedConstructor) {
	Engine::MouseButtonReleasedEvent a(1);

	int32_t releasedButton = a.getreleasedButton();

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_TRUE(releasedButton); //!< Checking if button is released 

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryMouse); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryMouse)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::MouseButtonReleased); //!< Checking if type is the MouseButtonReleased
}
TEST(EventsTests, MouseMovedConstructor) {
	Engine::MouseMovedEvent a(100, 200);

	int32_t xPos = a.getXPos();
	int32_t yPos = a.getYPos();
	auto Pos = a.getPos();
	int32_t NewPos = (Pos.x, Pos.y);

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();	

	EXPECT_EQ(xPos, 100); //!< Checking if X pos is correct
	EXPECT_EQ(yPos, 200); //!< Checking if Y pos is correct	

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryMouse); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryMouse)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::MouseMoved); //!< Checking if type is the MouseMoved
}
TEST(EventsTests, MouseScrollConstructor) {
	Engine::MouseScrollEvent a(50, 20);

	double xOffPos = a.getXOffsetPos();
	double yOffPos = a.getYOffsetPos();	

	int32_t category = a.getCategoryFlags();
	Engine::EventType type = a.getEventType();
	Engine::EventType staticType = a.getStaticType();

	EXPECT_EQ(xOffPos, 50); //!< Checking if X offset pos is correct
	EXPECT_EQ(yOffPos, 20); //!< Checking if Y offset pos is correct	

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryInput + Engine::EventCategory::EventCategoryMouse); //!< Checking if its in the right categorys
	EXPECT_TRUE(a.isInCategory(Engine::EventCategory::EventCategoryMouse)); //!< Checking if category flags are set correctly
	EXPECT_EQ(type, staticType); //!< Checking if static type is same as run time type
	EXPECT_EQ(type, Engine::EventType::MouseScrolled); //!< Checking if type is the Scrolled
}
