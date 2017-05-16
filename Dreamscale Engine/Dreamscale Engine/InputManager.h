#pragma once
#include <iostream>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update();
	
private:
	
	bool wasKeyPressed(unsigned int key);
	bool wasKeyReleased(unsigned int key);

	bool isKeyDown(unsigned int key);
	bool isKeyUp(unsigned int key);

};

