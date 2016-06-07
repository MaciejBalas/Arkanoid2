#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_font.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 800;
const float FPS = 60;

class Map
{
	int Map_arr[6][10];
	int left_border = 112;
	int right_border = 912;
	int up_border = 100;
	int block_width = 80;
	int block_height = 60;

public:
	Map()
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				Map_arr[i][j] = 1;
			}
		}
	}

	void New_map()
	{
		srand(time(NULL));

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				Map_arr[i][j] = rand()%2;
			}
		}
	}

	void Draw()
	{
		
		int x1, y1, x2, y2;

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Map_arr[i][j] == 1)
				{
					x1 = left_border + j*block_width;
					y1 = up_border + i*block_height;
					x2 = x1 + block_width -1;
					y2 = y1 + block_height -1;
					al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 10, 10, al_map_rgb(150, 60, 60));
				}
			}
		}
	}


};

void init()
{
	al_init();
	al_install_keyboard();
	al_init_font_addon();
	al_init_primitives_addon();
}

int main()
{

/////////////////////////////////////////////////////////// INITIALIZATION
	float x;
	x = 442;
	Map map;

	init();
	ALLEGRO_DISPLAY *Screen=nullptr;
	
	ALLEGRO_KEYBOARD_STATE Keyboard;
	ALLEGRO_COLOR BACKGROUND = al_map_rgb(130, 130, 130);	//CONSTANT COLOR FOR BACKGROUND
	ALLEGRO_BITMAP *PLAYER = al_create_bitmap(140, 30);	//CREATION OF BITMAP
	al_set_target_bitmap(PLAYER);	//SELECTING BITMAP FOR ALLEGRO TO MAKE CHANGES ON IT
	al_clear_to_color(al_map_rgb(200, 0, 150));	//SETTING A COLOR OF PLAYER
	ALLEGRO_FONT *Font = al_create_builtin_font();

	Screen = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);	// CREATING A WINDOW

	if (Screen == nullptr)
	{
		al_show_native_message_box(Screen, "ERROR", "NULL", "sth broke", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}

	al_set_window_title(Screen, "Arkanoid");// TITLE

///////////////////////////////////////////////////////////// MAIN LOOP

	al_get_keyboard_state(&Keyboard);//FIRST CHECKING OF KEYBOARD BUTTON STATUS SO THE MAIN LOOP WILL WORK

	al_set_target_bitmap(al_get_backbuffer(Screen));	// TO MAKE CHANGES TO THE SCREEN I NEED TO SELECT IT

	map.New_map();

	while (!al_key_down(&Keyboard,ALLEGRO_KEY_ESCAPE))
	{
		al_get_keyboard_state(&Keyboard);
		al_clear_to_color(BACKGROUND);		// SETTING BACKGROUND
		al_draw_bitmap(PLAYER, x, 700, 0);	// DRAWING ACTUAL POSITION OF THE PLAYER
		al_draw_text(Font, al_map_rgb(255, 255, 255), 10, 10, 0, "HIGHSCORE:");

		if (al_key_down(&Keyboard, ALLEGRO_KEY_LEFT))		//MOVING LEFT
		{
			x = x - 10;
			
			if (x<=0)
			{
				x = 0;
			}
		}	 

		if (al_key_down(&Keyboard, ALLEGRO_KEY_RIGHT))	//MOVING RIGHT
		{
			x = x + 10;

			if (x >= 900)
			{
				x = 900;
			}
		}
		
		map.Draw();

		al_flip_display();
		al_rest(0.016);	//REST NEEDED TO ENSURE ~60 FPS RENDERING
	}

	al_destroy_display(Screen);

	return 0;
}