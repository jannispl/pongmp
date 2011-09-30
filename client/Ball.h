class Ball;

#ifndef _BALL_H
#define _BALL_H

class Ball
{
public:
	Ball();
	~Ball();

	bool initialize();
	void deinitialize();

	bool process();
	void draw();

	void setAngle(float fAngle);
	float getAngle();
	void setVelocity(float fVelX, float fVelY);
	void getVelocity(float &fVelX, float &fVelY);
	void getPosition(float &fPosX, float &fPosY);
	void setPosition(float fPosX, float fPosY);

private:
	float m_fPosX;
	float m_fPosY;
	float m_fAngle;
	float m_fVelX;
	float m_fVelY;
	bool m_bInteraction;

	ALLEGRO_BITMAP *m_pBitmap;
};

#endif
