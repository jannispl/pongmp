#include "StdInc.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

bool Graphics::initialize()
{
	m_pDisplay = al_create_display(SCREEN_W, SCREEN_H);
	if (!m_pDisplay)
	{
		return false;
	}

	/*m_pDefaultFont = al_load_ttf_font("miscfs.ttf", 72, 0);
	if (!m_pDefaultFont)
	{
		return false;
	}*/

	return true;
}

void Graphics::deinitialize()
{
	//al_destroy_font(m_pDefaultFont);
	al_destroy_display(m_pDisplay);
}

bool Graphics::process()
{
	return true;
}

void Graphics::draw()
{
	al_set_target_bitmap(al_get_backbuffer(m_pDisplay));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	g_pGame->getPlatform(0)->draw();
	g_pGame->getPlatform(1)->draw();

	//al_draw_text(m_pDefaultFont, al_map_rgb(255, 255, 255), (SCREEN_W)/2, (SCREEN_H)/4, ALLEGRO_ALIGN_CENTRE, "hello world");
}

ALLEGRO_DISPLAY *Graphics::getDisplay()
{
	return m_pDisplay;
}
