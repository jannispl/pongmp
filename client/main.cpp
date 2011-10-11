#include "StdInc.h"
#include "Game.h"
#include <allegro5/allegro_primitives.h>

Game *g_pGame = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if (!al_init())
	{
		return -1;
	}

    al_init_font_addon(); // initialize the font addon
    if (!al_init_ttf_addon())
	{
		return -1;
	}
	if (!al_init_primitives_addon())
	{
		return -1;
	}
	if (!al_install_keyboard())
	{
		return -1;
	}

	g_pGame = new Game();

	if (!g_pGame->initialize())
	{
		return -1;
	}

	g_pGame->run();

	g_pGame->deinitialize();

	return 0;
}
