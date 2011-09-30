#include <allegro5/allegro.h>
#include "StdInc.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	memset(m_bKeyState, 0, sizeof(bool) * NUMKEYS);
}

Keyboard::~Keyboard()
{
}

void Keyboard::handleKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case ALLEGRO_KEY_UP:
		m_bKeyState[UP] = true;
		break;

	case ALLEGRO_KEY_DOWN:
		m_bKeyState[DOWN] = true;
		break;
	}
}

void Keyboard::handleKeyUp(int iKeyCode)
{
	switch (iKeyCode)
	{
	case ALLEGRO_KEY_UP:
		m_bKeyState[UP] = false;
		break;

	case ALLEGRO_KEY_DOWN:
		m_bKeyState[DOWN] = false;
		break;
	}
}

bool Keyboard::isKeyDown(int iKey)
{
	if (iKey < 0 || iKey >= NUMKEYS)
	{
		return false;
	}

	return m_bKeyState[iKey];
}
