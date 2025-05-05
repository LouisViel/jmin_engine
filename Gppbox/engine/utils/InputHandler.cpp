#include <imgui.h>
#include "InputHandler.hpp"
#include "app/M.hpp"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

sf::RenderWindow* InputHandler::window = nullptr;
void InputHandler::setWindow(sf::RenderWindow* window)
{
	InputHandler::window = window;
}

bool InputHandler::hasFocus()
{
	if (!window) return false;
	return window->hasFocus();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

bool InputHandler::canUseMouse()
{
	ImGuiIO& io = ImGui::GetIO();
	return !io.WantCaptureMouse;
}

bool InputHandler::canUseKeyboard()
{
	ImGuiIO& io = ImGui::GetIO();
	return !io.WantCaptureKeyboard;
}

bool InputHandler::canUse()
{
	ImGuiIO& io = ImGui::GetIO();
	return !(io.WantCaptureMouse || io.WantCaptureKeyboard);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


sf::Vector2f InputHandler::getHorizontal()
{
	bool leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
	bool leftPad = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
	bool rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	bool rightPad = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
	float axisJoy = getJoystickAxis(JoystickAxis::LeftHorizontal);
	float padJoy = getJoystickAxis(JoystickAxis::PadHorizontal);

	sf::Vector2f result;
	if (leftKey || leftPad) result.x = 1.0f;
	else { GET_AXIS_MULTIPLE(result.x, < 0.0f, ({ axisJoy, padJoy })); }
	if (rightKey || rightPad) result.y = 1.0f;
	else { GET_AXIS_MULTIPLE(result.y, > 0.0f, ({ axisJoy, padJoy })); }
	return result;
}

sf::Vector2f InputHandler::getVertical()
{
	bool downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	bool downPad = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
	bool upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
	bool upPad = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	float axisJoy = getJoystickAxis(JoystickAxis::LeftVertical);
	float padJoy = getJoystickAxis(JoystickAxis::PadVertical);

	sf::Vector2f result;
	if (downKey || downPad) result.x = 1.0f;
	else { GET_AXIS_MULTIPLE(result.x, < 0.0f, ({ axisJoy, padJoy })); }
	if (upKey || upPad) result.y = 1.0f;
	else { GET_AXIS_MULTIPLE(result.y, > 0.0f, ({ axisJoy, padJoy })); }
	return result;
}

bool InputHandler::getFire()
{
	bool fireKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);
	bool triggerJoy = isJoystickPressed(JoystickButton::TriggerRight);
	bool buttonJoy = isJoystickPressed(JoystickButton::Right);
	return fireKey || triggerJoy || buttonJoy;
}

bool InputHandler::getSwitch()
{
	bool switchKey = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	bool spaceKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	bool triggerJoy = isJoystickPressed(JoystickButton::TriggerLeft);
	bool buttonJoy = isJoystickPressed(JoystickButton::Left);
	return switchKey || spaceKey || triggerJoy || buttonJoy;
}

bool InputHandler::getDebug()
{
	bool debugKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);
	bool debugPad = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Multiply);
	bool debugJoy = isJoystickPressed(JoystickButton::MenuLeft);
	return debugKey || debugPad || debugJoy;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


bool InputHandler::getFrameFire()
{
	bool fire = InputHandler::getFire();
	if (wasFirePressed != fire) {
		wasFirePressed = fire;
		return fire;
	}
	return false;
}

bool InputHandler::getFrameSwitch()
{
	bool _switch = InputHandler::getSwitch();
	if (wasSwitchPressed != _switch) {
		wasSwitchPressed = _switch;
		return _switch;
	}
	return false;
}

bool InputHandler::getFrameMouseLeft()
{
	bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (wasLeftClick != click) {
		wasLeftClick = click;
		return click;
	}
	return false;
}

bool InputHandler::getFrameMouseRight()
{
	bool click = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	if (wasRightClick != click) {
		wasRightClick = click;
		return click;
	}
	return false;
}