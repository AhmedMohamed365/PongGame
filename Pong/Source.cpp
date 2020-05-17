#include <allegro5/allegro.h>
#include <allegro5/fullscreen_mode.h>
#include <allegro5/allegro_color.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<cmath>
#include<string>
#include <algorithm>
using namespace std;
//|| ex >= ScreenWidth || ey >= ScreenHeight|| ex <= 0 || ey <= 0
#define ScreenWidth 500 
#define ScreenHeight 500
float x = 0, y = 0;
float ex = ScreenWidth - 100, ey = 0;
float xRand, yRand;
int dir = -1, rectDir = -1, cDir = 3;
int playerScore = 0, AiScore = 0;
enum { Down = 1, UP, RIGHT, LEFT };
bool updatePosition(float& x, float& y, float& ey, float& xRand, float& yRand) {
	if (x > ScreenWidth || y > ScreenHeight || x < 0 || y < 0 || x + 50>ScreenWidth || y + 50>ScreenHeight || ey + 100 > ScreenHeight || ey < 0 || xRand >= ScreenWidth || yRand >= ScreenHeight || xRand <= 0 || yRand <= 0) {
		//There is collision to the borders of the screen	
			//to prevent auto rect from going up or down
			/*if (ey + 100 > ScreenHeight)
				rectDir = UP;
			else if (ey <= 0)
				rectDir = Down;
				*/

				//To prevent circle going anyway
		if (yRand >= ScreenHeight)
			cDir = UP;
		else if (yRand <= 0)
			cDir = Down;

		if (xRand >= ScreenWidth)
		{

			playerScore++;
			xRand = 400;
			cDir = LEFT;
			return false;
		}


		else if (xRand < 0)
		{
			AiScore++;
			xRand = 400;
			cDir = RIGHT;
			return false;

		}


		/*	if (xRand > ScreenWidth&& yRand > ScreenHeight) {
				xRand -= 50;
				yRand -= 50;
			}
			*/
	}
	//No collision to the screen
	else
		return false;

}
bool Collision(float x, float y, float& ey, float& ex, float& xRand, float& yRand) {
	//finall collision :
	/* if (yRand < y + 50)
			 cDir = -2;
		 else if (yRand > y + 50)
			 cDir = -1;
		 else if (yRand == y + 50)*/
		 //      ||
		 //Player Rect collision
	if (sqrt(pow(x + 25 - xRand, 2) + pow(y + 50 - yRand, 2)) < 50)
	{
		if (xRand <= x)
			cDir = LEFT;
		else if (yRand > y + 50)
			cDir = -1;
		else if (yRand < y + 50)
			cDir = -2;
		else if (yRand == y + 50)
			cDir = RIGHT;

		return true;
	}

	/* else if (sqrt(pow(x + 25 - xRand, 2) + pow(y + 50 - yRand, 2))>=25) {
		 if (yRand < y + 50)
			 cDir = -4;
		 else if (yRand > y + 50)
			 cDir = -3;
		 else if (yRand == y + 50)
			 cDir = LEFT;
		 return true;
	 }
	 */
	 //----------------------------------------------------------------

	else if (sqrt(pow(ex + 25 - xRand, 2) + pow(ey + 50 - yRand, 2)) < 50)
	{
		if (xRand > ex + 50)
			cDir = RIGHT;
		else if (yRand < ey + 50)
			cDir = -4;
		else if (yRand > ey + 50)
		{
			cDir = -3;
		}
		else if (yRand == ey + 50)
			cDir = LEFT;

		// of player Rect
		return true;
	}

}

int main() {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* Timer;
	ALLEGRO_TIMER* playerRate;

	//Installing add-ons and intialize games
	al_init();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();


	ALLEGRO_FONT* font = al_load_font("andlso.ttf", 36, NULL);
	//Intilization
	//srand(-400);
	xRand = rand() % 400; yRand = rand() % 400;
	const float FPS = 60.0f, playerSpeed = 30.0f;



	bool run = true;

	display = al_create_display(ScreenWidth, ScreenHeight);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());

	Timer = al_create_timer(1 / FPS);
	playerRate = al_create_timer(1 / playerSpeed);
	al_register_event_source(queue, al_get_timer_event_source(Timer));
	al_register_event_source(queue, al_get_timer_event_source(playerRate));

	ALLEGRO_COLOR white, BLACK;
	ALLEGRO_KEYBOARD_STATE keyState;
	white = al_map_rgb_f(1, 1, 1);
	BLACK = al_map_rgb_f(0, 0, 0);
	al_start_timer(playerRate);
	al_start_timer(Timer);
	al_init_primitives_addon();
	ALLEGRO_EVENT event;

	while (run) {
		al_wait_for_event(queue, &event);
		al_get_keyboard_state(&keyState);
		al_clear_to_color(white);
		//al_draw_rectangle(ex, ey, ex-100,ex-100 , BLACK, 5.0f);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			run = false;
		else if (event.timer.source == Timer) {
			if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
				y -= 5;
				dir = UP;

			}

			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
				x += 5;
				dir = RIGHT;
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
				y += 5;
				dir = Down;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
				x -= 5;
				dir = LEFT;
			}
			if (updatePosition(x, y, ey, xRand, yRand)) {
				if (dir == Down)
					y -= 5;
				else if (dir == RIGHT)
					x -= 5;
				else if (dir == LEFT)
					x += 5;
				else if (dir == UP)
					y += 5;

			}
			else
				dir = 0;


			//go op or down

					/*	if (rectDir == Down)
							ey += 20;
						else if (rectDir == UP)
							ey -= 20;
							*/


		}
		else if (event.timer.source == playerRate) {
			//Random movment of the circle
			if (cDir == Down)
				yRand += 5;
			else if (cDir == UP)
				yRand -= 5;
			if (cDir == LEFT)
				xRand -= 10;
			else if (cDir == RIGHT)
				xRand += 10;

			if (Collision(x, y, ey, ex, xRand, yRand))
			{
				if (cDir == -1)
				{
					xRand += 10;
					yRand -= 10;
				}
				else if (cDir == -2) {
					xRand += 10;
					yRand += 10;
				}
				else if (cDir == -3)
				{
					xRand -= 10;
					yRand -= 10;
				}
				else if (cDir == -4) {
					xRand -= 10;
					yRand += 10;
				}
			}

			if (ex > ScreenWidth)
				ex -= 50;
			if (ey > ScreenHeight)
				ey -= 100;
			if (sqrt(pow(ex + 25 - xRand, 2) + pow(ey + 50 - yRand, 2)) >= 55)
			{
				if (ey <= yRand)
					ey += 5;
				else
					ey -= 5;
				if (ex >= xRand)
					ex -= 5;
				else
					ex += 5;

			}

		}

		al_draw_filled_circle(xRand, yRand, 25, BLACK);

		al_draw_filled_rectangle(250, 0, 255, 500, BLACK);
		al_draw_filled_rectangle(x, y, x + 50, y + 100, BLACK);
		al_draw_filled_rectangle(ex, ey, ex + 50, ey + 100, BLACK);
		//al_draw_rectangle(400, 400, 400 + x, 400 + y, BLACK, 5.0f);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 150, 0, ALLEGRO_ALIGN_CENTER, "PlayerScore:%d", playerScore);
		al_draw_textf(font, al_map_rgb(0, 0, 0), 380, 0, ALLEGRO_ALIGN_CENTER, "CpuScore:%d", AiScore);


		al_flip_display();
	}
	al_destroy_timer(Timer);
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_timer(playerRate);

	return 0;
}


//previous AI
			/*	if (ey <= yRand)
				ey += 5;
			else if(ey>yRand+10)
				ey -= 5;
			if (ex <= xRand+25)
				ex += 5;
			else if(ex>xRand+20)
				ex -= 5;*/