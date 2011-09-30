class Keyboard;

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	enum
	{
		UP, DOWN,
		NUMKEYS
	};

	void handleKeyDown(int iKeyCode);
	void handleKeyUp(int iKeyCode);
	bool isKeyDown(int iKey);

private:
	bool m_bKeyState[NUMKEYS];
};

#endif
