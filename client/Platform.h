class Platform;

#ifndef _PLATFORM_H
#define _PLATFORM_H

class Platform
{
public:
	Platform(float fX);
	~Platform();

	bool initialize();
	void deinitialize();

	bool process();
	void draw();

	void setPosition(float fPosX, float fPosY);
	void getPosition(float &fPosX, float &fPosY);
	void setVelocity(float fVelocity);
	float getVelocity();
	void accelerate(float fAcceleration);
	void decelerate(float fDeceleration);

	enum PropulsionState {OFF, UP, DOWN};

	PropulsionState getPropulsionState();
	void setPropulsionState(PropulsionState propulsionState);

private:
	float m_fPosX;
	float m_fPosY;
	float m_fVelocity;
	PropulsionState m_propulsionState;

	ALLEGRO_BITMAP *m_pBitmap;
};

#endif
