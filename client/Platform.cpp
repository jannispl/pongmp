#include "StdInc.h"
#include "Platform.h"

Platform::Platform(float fX)
	: m_bInteraction(false)
{
	m_fPosX = fX;
	m_fPosY = SCREEN_H / 2.0f - PLATFORM_H / 2.0f;
}

Platform::~Platform()
{
}

bool Platform::initialize()
{
	m_pBitmap = al_create_bitmap(PLATFORM_W, PLATFORM_H);
	if (!m_pBitmap)
	{
		return false;
	}
	
	al_set_target_bitmap(m_pBitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	return true;
}

void Platform::deinitialize()
{
	al_destroy_bitmap(m_pBitmap);
}

bool Platform::process()
{
	m_bInteraction = false;
	bool bInteraction = m_bInteraction;

	bool bRedraw = bInteraction;

	if (m_bInteraction)
	{
		if (m_fVelocity > 7.0f)
		{
			m_fVelocity = 7.0f;
		}
		else if (m_fVelocity < -7.0f)
		{
			m_fVelocity = -7.0f;
		}
	}
	else
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
	}

	m_fPosY += m_fVelocity;
	if (m_fPosY < 0)
	{
		m_fPosY = 0;
		m_fVelocity = 0.0f;
	}
	else if (m_fPosY > SCREEN_H - PLATFORM_H)
	{
		m_fPosY = SCREEN_H - PLATFORM_H;
		m_fVelocity = 0.0f;
	}

	return bRedraw;
}

void Platform::draw()
{
	al_draw_bitmap(m_pBitmap, m_fPosX, m_fPosY, 0);
}

void Platform::setPosition(float fPosX, float fPosY)
{
	m_fPosX = fPosX;
	m_fPosY = fPosY;
}

void Platform::getPosition(float &fPosX, float &fPosY)
{
	fPosX = m_fPosX;
	fPosY = m_fPosY;
}

void Platform::setVelocity(float fVelocity)
{
	m_fVelocity = fVelocity;
	m_bInteraction = true;
}

float Platform::getVelocity()
{
	return m_fVelocity;
}

void Platform::accelerate(float fAcceleration)
{
	m_bInteraction = true;
	m_fVelocity += fAcceleration;
}

void Platform::decelerate(float fDeceleration)
{
	m_bInteraction = true;
	m_fVelocity -= fDeceleration;
}

