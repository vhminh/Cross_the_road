#include "Buffer.h"
#include "Function.h"
#include <ctime>
#include <Windows.h>
#include <string>
#include <algorithm>
#include "Constants.h"
#include "Game.h"
#include "Menu.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

// Global variables
int WIDTH = 120; // width of the console
int HEIGHT = 35; // height of the console
int LANE_SIZE = 5; // size of the lane
int DISTANCE_BETWEEN_CARS = 17; // minimum distance between two cars (it should > 14 because the car's width is 14)
int DISTANCE_BETWEEN_TRUCKS = 24; // > 21
int DISTANCE_BETWEEN_DINOS = 18; // > 15
int DISTANCE_BETWEEN_BIRDS = 6; // > 3
int MAX_CARS = 3;
int MAX_TRUCK = 2;
int MAX_DINO = 3;
int MAX_BIRD = 5;
double PERSON_SPEED = 0.05;
double OBSTACLE_BASE_SPEED = 0.005;
double OBSTACLE_SPEED_SCALE = 0.003;
double RED_LIGHT_TIME = 2000; // in millisec
double GREEN_LIGHT_TIME = 3000;
bool GAME_IS_OVER = false;
double RANDOM_BIRD_SPEED = 0.03;
bool sound = true;
int difficulty = 0; // 0: ez, 1: normal, else: hard

int main() {
	GetAsyncKeyState(NULL); // refresh the keystate
	// create seed for random numbers
	srand(time(NULL));
	// set console size
	system("mode con: cols=120 lines=40");
	fixConsoleSize();
	// hide the cursor
	setCursorVisible(false);
	// create Game object and run
	Game g;
	Menu menu;
	menu.menuCall(g);
	//g.run();
	return 0;
}
