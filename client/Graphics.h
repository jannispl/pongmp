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

	ALLEGRO_DISPLAY *getDisplay();

private:
	ALLEGRO_DISPLAY *m_pDisplay;
	ALLEGRO_FONT *m_pDefaultFont;
};

#endif
