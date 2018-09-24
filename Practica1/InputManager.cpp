#include <iostream>

#include "Headers/InputManager.h"
#include "Headers/TimeManager.h"

InputManager::InputCodes InputManager::toApplicationKey(int key) {
	switch (key) {
	case 256:
		return InputCodes::kEscape;
	case 87:
		return InputCodes::W;
	case 83:
		return InputCodes::S;
	case 65:
		return InputCodes::A;
	case 68:
		return InputCodes::D;
	case 265:
		return InputCodes::Up;
	case 264:
		return InputCodes::Down;
	case 263:
		return InputCodes::Left;
	case 262:
		return InputCodes::Right;
	case 69:
		return InputCodes::E;
	case 111:
		return InputCodes::e;
	case 81:
		return InputCodes::Q;
	case 113:
		return InputCodes::q;
	case 32:
		return InputCodes::Space;

	}
}

InputManager::State InputManager::toApplicationState(int state) {
	switch (state) {
	case 0:
		return State::RELESED;
	case 1:
		return State::PRESSED;
	}
}

void InputManager::keyPressed(InputCodes code, float deltaTime, State state) {
	keyState[code] = state;
}


void InputManager::mouseMoved(float mouseX, float mouseY) {
	lastMousePos.x = mouseX;
	lastMousePos.y = mouseY;
}

void InputManager::mouseClicked(MouseCodes code) {
	switch (code) {
	case button_right:
		std::cout << "lastMousePos.x:" << lastMousePos.x << std::endl;
		break;
	case button_left:
		std::cout << "lastMousePos.y:" << lastMousePos.y << std::endl;
		break;
	case button_middle:
		std::cout << "lastMousePos.x:" << lastMousePos.x << std::endl;
		std::cout << "lastMousePos.y:" << lastMousePos.y << std::endl;
		break;
	}
}

void InputManager::mouseScroll(float yoffset) {
}

void InputManager::do_movement(float deltaTime) {
	if (keyState[InputCodes::W] || keyState[InputCodes::w] || keyState[InputCodes::Up])
	{
		zoom += 0.015f;
	}
	else if (keyState[InputCodes::S] || keyState[InputCodes::s] || keyState[InputCodes::Down])
	{
		zoom -= 0.015f;
	}
}
