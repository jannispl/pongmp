#include "StdInc.h"
#include "Game.h"

Game *g_pGame = NULL;

#if 0
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	float bouncer_x = 10.0f;
	float bouncer_y = SCREEN_H / 2.0 - PLATFORM_H / 2.0;
	float bouncer_dx = -4.0, bouncer_dy = 4.0;
	bool redraw = true;
	bool doexit = false;

	bool key[4] = { false, false, false, false };

	if (!al_init())
	{
		error("failed to initialize allegro!\n");
		return -1;
	}

    al_init_font_addon(); // initialize the font addon
    if (!al_init_ttf_addon())
	{
		error("failed to initialize ttf addon");
		return -1;
	}
	if (!al_install_keyboard())
	{
		error("failed to initialize the keyboard!\n");
		return -1;
	}
    ALLEGRO_FONT *font = al_load_ttf_font("miscfs.ttf", 72, 0); // load the font | Font from Larabie Free Fonts
	if (!font)
	{
		error("failed to load font");
		return -1;
	}


	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		error("failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display)
	{
		error("failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	bouncer = al_create_bitmap(PLATFORM_W, PLATFORM_H);
	if (!bouncer)
	{
		error("failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		error("failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_flip_display();

	al_start_timer(timer);

	float fVelY = 0.0f;

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			bool changed = false;
			if (key[KEY_UP])
			{
				changed = true;
				fVelY -= 0.65f;
			}
			else if (key[KEY_DOWN])
			{
				changed = true;
				fVelY += 0.65f;
			}

			if (changed)
			{
				if (fVelY > 10.0f)
				{
					fVelY = 10.0f;
				}
				else if (fVelY < -10.0f)
				{
					fVelY = -10.0f;
				}
			}
			else
			{
				if (fVelY < 0.0f)
				{
					fVelY += 0.15f;
					if (fVelY > 0.0f) fVelY = 0.0f;
				}
				else if (fVelY > 0.0f)
				{
					fVelY -= 0.15f;
					if (fVelY < 0.0f) fVelY = 0.0f;
				}
			}

			bouncer_y += fVelY;
			if (bouncer_y < 0)
			{
				bouncer_y = 0;
				fVelY = 0.0f;
			}
			else if (bouncer_y > SCREEN_H - PLATFORM_H)
			{
				bouncer_y = SCREEN_H - PLATFORM_H;
				fVelY = 0.0f;
			}
			
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT: 
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT: 
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

			char tmp[128];
			sprintf(tmp, "%.5f", fVelY);

			al_draw_text(font, al_map_rgb(255, 255, 255), (SCREEN_W)/2, (SCREEN_H)/4, ALLEGRO_ALIGN_CENTRE, tmp);// draw the text

			al_flip_display();
		}
	}

	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
#endif

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
	if (!al_install_keyboard())
	{
		return -1;
	}

	g_pGame = new Game();

	if (!g_pGame->initialize())
	{
		return 1;
	}

	g_pGame->run();

	g_pGame->deinitialize();

	return 0;
}
