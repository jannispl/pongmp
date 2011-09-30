class Game;

#ifndef _GAME_H
#define _GAME_H

#include <allegro5/allegro.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Graphics.h"
#include "Keyboard.h"
#include "Platform.h"
#include "Ball.h"
#include "Network.h"

const float FPS = 60.0f;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int PLATFORM_W = 10;
const int PLATFORM_H = 50;
const int BALL_SIZE = 15;

class Game
{
public:
	Game();
	~Game();

	bool initialize();
	void run();
	void deinitialize();

	Graphics *getGraphics();
	Keyboard *getKeyboard();
	Platform *getPlatform(int i);
	Network *getNetwork();

private:
	Graphics *m_pGraphics;
	Keyboard *m_pKeyboard;
	Platform *m_pPlatform[2];
	Ball *m_pBall;
	Network *m_pNetwork;

	ALLEGRO_EVENT_QUEUE *m_pEventQueue;
	ALLEGRO_TIMER *m_pFrameTimer;
	ALLEGRO_TIMER *m_pNetworkTimer;

	bool m_bRunning;
};

#endif
