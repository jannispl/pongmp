#include "StdInc.h"
#include "Platform.h"

Platform::Platform(float fX)
{
	m_fPosX = fX;
	m_fPosY = SCREEN_H / 2.0f - PLATFORM_H / 2.0f;
	m_fVelocity = 0.0f;
	m_propulsionState = OFF;
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
	if(m_propulsionState == UP)
	{
		m_fVelocity -= 0.6f;
		
		// speed limiter
		if (m_fVelocity < -7.0f)
		{
			m_fVelocity = -7.0f;
		}
	}
	else if(m_propulsionState == DOWN)
	{
		m_fVelocity += 0.6f;
		
		// speed limiter
		if (m_fVelocity > 7.0f)
		{
			m_fVelocity = 7.0f;
		}
	}
	else // no propulsion
	{
		if (m_fVelocity < 0.0f)
		{
			m_fVelocity += 0.15f;
			if (m_fVelocity > 0.0f) m_fVelocity = 0.0f;
		}
		else if (m_fVelocity > 0.0f)
		{
			m_fVelocity -= 0.15f;
			if (m_fVelocity < 0.0f) m_fVelocity = 0.0f;
		}
	}


	// update position
	float oldPos = m_fPosY;
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

	return oldPos != m_fPosY;
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
}

float Platform::getVelocity()
{
	return m_fVelocity;
}

void Platform::accelerate(float fAcceleration)
{
	m_fVelocity += fAcceleration;
}

void Platform::decelerate(float fDeceleration)
{
	m_fVelocity -= fDeceleration;
}

Platform::PropulsionState Platform::getPropulsionState() {
	return m_propulsionState;
}

void Platform::setPropulsionState(Platform::PropulsionState propulsionState) {
	m_propulsionState = propulsionState;
}