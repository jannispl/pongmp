#include "StdInc.h"
#include "Ball.h"
#include <math.h>

Ball::Ball()
	: m_bInteraction(false), m_fAngle(0.0f), m_fVelX(0.0f), m_fVelY(0.0f)
{
	m_fPosX = SCREEN_W / 2.0f - BALL_SIZE / 2.0f;
	m_fPosY = SCREEN_H / 2.0f - BALL_SIZE / 2.0f;
}

Ball::~Ball()
{
}

bool Ball::initialize()
{
	m_pBitmap = al_create_bitmap(BALL_SIZE, BALL_SIZE);
	if (!m_pBitmap)
	{
		return false;
	}
	
	al_set_target_bitmap(m_pBitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	return true;
}

void Ball::deinitialize()
{
	al_destroy_bitmap(m_pBitmap);
}

bool Ball::process()
{
	bool bInteraction = m_bInteraction;
	m_bInteraction = false;

	bool bRedraw = bInteraction;

	if (m_bInteraction)
	{
		/*if (m_fVelocity > 10.0f)
		{
			m_fVelocity = 10.0f;
		}
		else if (m_fVelocity < -10.0f)
		{
			m_fVelocity = -10.0f;
		}*/
	}
	/*else
	{
		if (m_fVelocity < 0.0f)
		{
			bRedraw = true;
			m_fVelocity += 0.15f;
			if (m_fVelocity > 0.0f) m_fVelocity = 0.0f;
		}
		else if (m_fVelocity > 0.0f)
		{
			bRedraw = true;
			m_fVelocity -= 0.15f;
			if (m_fVelocity < 0.0f) m_fVelocity = 0.0f;
		}
	}*/

	m_fPosX += sin(m_fAngle * (3.1415926f / 180.0f)) * m_fVelX;
	m_fPosY += cos(m_fAngle * (3.1415926f / 180.0f)) * m_fVelY;

	if (m_fPosX < 0.0f)
	{
		m_fPosX = 0.0f;
		m_fVelX = -m_fVelX;
	}
	else if (m_fPosX > SCREEN_W - BALL_SIZE)
	{
		m_fPosX = SCREEN_W - BALL_SIZE;
		m_fVelX = -m_fVelX;
	}

	if (m_fPosY < 0.0f)
	{
		m_fPosY = 0.0f;
		m_fVelY = -m_fVelY;
	}
	else if (m_fPosY > SCREEN_H - BALL_SIZE)
	{
		m_fPosY = SCREEN_H - BALL_SIZE;
		m_fVelY = -m_fVelY;
	}

	return bRedraw;
}

void Ball::draw()
{
	al_draw_bitmap(m_pBitmap, m_fPosX, m_fPosY, 0);
}

void Ball::setAngle(float fAngle)
{
	m_fAngle = fAngle;
}

float Ball::getAngle()
{
	return m_fAngle;
}

void Ball::setVelocity(float fVelX, float fVelY)
{
	m_fVelX = fVelX;
	m_fVelY = fVelY;
	m_bInteraction = true;
}

void Ball::getVelocity(float &fVelX, float &fVelY)
{
	fVelX = m_fVelX;
	fVelY = m_fVelY;
}

void Ball::getPosition(float &fPosX, float &fPosY)
{
	fPosX = m_fPosX;
	fPosY = m_fPosY;
}

void Ball::setPosition(float fPosX, float fPosY)
{
	m_fPosX = fPosX;
	m_fPosY = fPosY;
}
