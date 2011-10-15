#include "StdInc.h"
#include "Game.h"
#include <stdio.h>

Game::Game()
	: m_bRunning(false)
{
	m_pGraphics = new Graphics();
	m_pKeyboard = new Keyboard();

	m_pPlatform[0] = new Platform(5);
	m_pPlatform[1] = new Platform(SCREEN_W - PLATFORM_W - 5);
	m_pBall = new Ball();

	m_pNetwork = new Network();
}

Game::~Game()
{
	delete m_pGraphics;
	delete m_pKeyboard;
	
	delete m_pPlatform[0];
	delete m_pPlatform[1];
	delete m_pBall;

	delete m_pNetwork;
}

bool Game::initialize()
{
	m_pNetwork->initialize();

	m_pFrameTimer = al_create_timer(1.0 / FPS);
	if (!m_pFrameTimer)
	{
		return false;
	}

	m_pNetworkTimer = al_create_timer(0.06);
	if (!m_pNetworkTimer)
	{
		return false;
	}

	if (!m_pGraphics->initialize())
	{
		al_destroy_timer(m_pFrameTimer);
		return false;
	}

	if (!m_pPlatform[0]->initialize() || !m_pPlatform[1]->initialize() || !m_pBall->initialize())
	{
		al_destroy_timer(m_pFrameTimer);
		return false;
	}

	m_pEventQueue = al_create_event_queue();
	if (!m_pEventQueue)
	{
		al_destroy_timer(m_pFrameTimer);
		return false;
	}

	al_register_event_source(m_pEventQueue, al_get_display_event_source(m_pGraphics->getDisplay()));
	al_register_event_source(m_pEventQueue, al_get_timer_event_source(m_pFrameTimer));
	al_register_event_source(m_pEventQueue, al_get_timer_event_source(m_pNetworkTimer));
	al_register_event_source(m_pEventQueue, al_get_keyboard_event_source());
	
	al_set_target_bitmap(al_get_backbuffer(m_pGraphics->getDisplay()));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(m_pFrameTimer);
	al_start_timer(m_pNetworkTimer);

	return true;
}

void Game::run()
{
	bool bRedraw = true;
	bool bSendPlatform = true;

	m_pBall->setAngle(-45.0f);
	m_pBall->setVelocity(3.2f, 3.2f);

	m_bRunning = true;
	do
	{
		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT t;
		al_init_timeout(&t, 0.005);
		//al_wait_for_event(m_pEventQueue, &ev);
		bool bGot = al_wait_for_event_until(m_pEventQueue, &ev, &t);

		if (bGot)
		{
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				m_bRunning = false;
				break;
			}
			else if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == m_pNetworkTimer)
			{
				if (bSendPlatform)
				{
					bSendPlatform = false;
					float fX, fY;
					m_pPlatform[0]->getPosition(fX, fY);
					m_pNetwork->updatePlatform(fY, m_pPlatform[0]->getVelocity(), m_pPlatform[0]->getPropulsionState());
				}
			}
			else if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == m_pFrameTimer)
			{
				m_pNetwork->process();

				if (m_pGraphics->process()) bRedraw = true;

				if (m_pKeyboard->isKeyDown(Keyboard::UP))
				{
					//m_pPlatform[0]->decelerate(0.60f);

					if (m_pPlatform[0]->getPropulsionState() != Platform::UP)
					{
						m_pPlatform[0]->setPropulsionState(Platform::UP);

						float fX, fY;
						m_pPlatform[0]->getPosition(fX, fY);
						m_pNetwork->updatePlatform(fY, m_pPlatform[0]->getVelocity(), Platform::UP);
					}
				}
				else if (m_pKeyboard->isKeyDown(Keyboard::DOWN))
				{
					//m_pPlatform[0]->accelerate(0.60f);

					if (m_pPlatform[0]->getPropulsionState() != Platform::DOWN)
					{
						m_pPlatform[0]->setPropulsionState(Platform::DOWN);

						float fX, fY;
						m_pPlatform[0]->getPosition(fX, fY);
						m_pNetwork->updatePlatform(fY, m_pPlatform[0]->getVelocity(), Platform::DOWN);
					}
				}
				else
				{
					if (m_pPlatform[0]->getPropulsionState() != Platform::OFF)
					{
						m_pPlatform[0]->setPropulsionState(Platform::OFF);

						float fX, fY;
						m_pPlatform[0]->getPosition(fX, fY);
						m_pNetwork->updatePlatform(fY, m_pPlatform[0]->getVelocity(), Platform::OFF);
					}
				}
				
				// sync the platforms
				//m_pPlatform[1]->setVelocity(m_pPlatform[0]->getVelocity());

				float fX, fY;
				m_pPlatform[0]->getPosition(fX, fY);
				float fX2, fY2;
				m_pPlatform[1]->getPosition(fX2, fY2);

				float fBallX, fBallY;
				m_pBall->getPosition(fBallX, fBallY);

	#if 0
				if (fBallX < fX + PLATFORM_W)
				{
					if (fBallY + BALL_SIZE < fY || fBallY - BALL_SIZE > fY + PLATFORM_H)
					{
						MessageBoxA(NULL, "lose tbh", "", 0);
						ExitProcess(0);
					}
					else
					{
						float fVelX, fVelY;
						m_pBall->getVelocity(fVelX, fVelY);
						m_pBall->setVelocity(-fVelX, fVelY);
					}
				}
				if (fBallX + BALL_SIZE > fX2)
				{
					if (fBallY + BALL_SIZE < fY2 || fBallY - BALL_SIZE > fY2 + PLATFORM_H)
					{
						MessageBoxA(NULL, "lose tbh", "", 0);
						ExitProcess(0);
					}
					else
					{
						float fVelX, fVelY;
						m_pBall->getVelocity(fVelX, fVelY);
						m_pBall->setVelocity(-fVelX, fVelY);
					}
				}
	#endif

				if (m_pPlatform[0]->process())
				{
					bRedraw = true;
					bSendPlatform = true;
				}
				if (m_pPlatform[1]->process()) bRedraw = true;
				if (m_pBall->process()) bRedraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				m_pKeyboard->handleKeyDown(ev.keyboard.keycode);
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				m_pKeyboard->handleKeyUp(ev.keyboard.keycode);
			}

		}

		if (/*bRedraw && */al_is_event_queue_empty(m_pEventQueue))
		{
			bRedraw = false;

			m_pGraphics->draw();
			for (int i = 0; i < 2; ++i)
			{
				m_pPlatform[i]->draw();
			}
			m_pBall->draw();
			
			al_flip_display();

			// some platform interpolation?
			if (m_pNetwork->m_iAvailBuffers == 2)
			{
				float fNow = Shared::getCurrentTime();
				float fFirstTime = m_pNetwork->m_fPosBufferTime[1];
				float fFirstVal = m_pNetwork->m_fPosBuffer[1];
				float fNewTime = m_pNetwork->m_fPosBufferTime[0];
				float fNewVal = m_pNetwork->m_fPosBuffer[0];

				float fDelta = fNow - fNewTime;
				if (fDelta <= fNewTime - fFirstTime)
				{
					float fInterpPos = fFirstVal + ((fNewVal - fFirstVal) / (fNewTime - fFirstTime)) * fDelta;

					/*char tmp[128];
					sprintf(tmp, "%f", fDelta);
					m_pGraphics->showStatusMessage(tmp);*/

					float fX, fY;
					m_pPlatform[1]->getPosition(fX, fY);
					m_pPlatform[1]->setPosition(fX, fInterpPos);
				}
			}
		}
	}
	while (m_bRunning);
}

void Game::deinitialize()
{
	m_pNetwork->deinitialize();

	m_pGraphics->deinitialize();
	m_pPlatform[0]->deinitialize();
	m_pPlatform[1]->deinitialize();
	m_pBall->deinitialize();

	al_destroy_timer(m_pFrameTimer);
	al_destroy_event_queue(m_pEventQueue);
}

Graphics *Game::getGraphics()
{
	return m_pGraphics;
}

Keyboard *Game::getKeyboard()
{
	return m_pKeyboard;
}

Platform *Game::getPlatform(int i)
{
	return m_pPlatform[i];
}

Network *Game::getNetwork()
{
	return m_pNetwork;
}
