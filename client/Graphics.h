class Graphics;

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool initialize();
	void deinitialize();

	bool process();
	void draw();

	void showStatusMessage(const std::string &sMessage, float fDuration = 0.0f);
	void clearStatusMessage();

	ALLEGRO_DISPLAY *getDisplay();

private:
	ALLEGRO_DISPLAY *m_pDisplay;
	ALLEGRO_FONT *m_pDefaultFont;

	std::string m_sStatusMessage;
	float m_fStatusEndTime;
};

#endif
