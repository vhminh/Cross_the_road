#include "Game.h"
#include "Constants.h"
#include "Function.h"
#include <Windows.h>
#include <string>
#include <algorithm>
#include <thread>
#include <conio.h>
#include <vector>
#include <iostream>
#include <fstream>

Game::Game() : buffer(WIDTH, HEIGHT + 1) {
	isPaused = false;
	reset(1);
	isRunning = true;
}

void Game::drawLanes() {
	for (int i = 0; i < WIDTH; ++i) {
		buffer.draw('_', i, LANE_SIZE - 1);
		buffer.draw('_', i, 2 * LANE_SIZE - 1);
		buffer.draw('_', i, 3 * LANE_SIZE - 1);
		buffer.draw('_', i, 4 * LANE_SIZE - 1);
		buffer.draw('_', i, 5 * LANE_SIZE - 1);
	}
}

void Game::drawLosingOptions() {
	buffer.draw("You have lost ", 45, 6 * LANE_SIZE - 1);
	buffer.draw("Press [Y] to start new game", 45, 6 * LANE_SIZE + 1);
	buffer.draw("Press [Q] to quit...", 45, 6 * LANE_SIZE + 3);
}

void Game::drawTrafficLight() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// draw red light
	if (trafficLightIsRed) {
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
		gotoXY(0, 3 * LANE_SIZE);
		std::cout << "  ";
		gotoXY(WIDTH - 2, 4 * LANE_SIZE);
		std::cout << "  ";
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		gotoXY(0, 3 * LANE_SIZE);
		std::cout << "  ";
		gotoXY(WIDTH - 2, 4 * LANE_SIZE);
		std::cout << "  ";
	}
	// draw 2 green light
	if (trafficLightIsRed) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		gotoXY(0, 3 * LANE_SIZE + 1);
		std::cout << "  ";
		gotoXY(WIDTH - 2, 4 * LANE_SIZE + 1);
		std::cout << "  ";
	}
	else {
		SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
		gotoXY(0, 3 * LANE_SIZE + 1);
		std::cout << "  ";
		gotoXY(WIDTH - 2, 4 * LANE_SIZE + 1);
		std::cout << "  ";
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Game::printInstruction() {
	buffer.draw("Level: " + std::to_string(level), 0, 0);
	std::string d[] = { "ez", "normal", "hard " };
	buffer.draw("Difficulty: " + d[difficulty], 0, 2);
	buffer.draw("[W][A][S][D] for movement     [P] to pause game       [R] to resume game", 20, 6 * LANE_SIZE - 1);
	buffer.draw("[X] to save game              [L] to load game        [ESC] to exit", 20, 6 * LANE_SIZE + 1);
}

void Game::hideInstruction() {
	gotoXY(20, 6 * LANE_SIZE - 1);
	std::cout << "                                                                                ";
	gotoXY(20, 6 * LANE_SIZE + 1);
	std::cout << "                                                                                ";
	gotoXY(20, 6 * LANE_SIZE + 3);
	std::cout << "                                                                                ";
}

void Game::handleUserInput() {
	const char ESC = 27;
	char c;
	std::string path;
	while (isRunning) {
		c = toupper(_getch());
		if (person.isDead) {
			if (c == 'Y') {
				reset(1);
				system("cls");
				resume();
			}
			else if (c == 'Q' || c == ESC) {
				exitGame();
			}
		}
		switch (c) {
		case 'P':
			isPaused = true;
			break;
		case 'R':
			isPaused = false;
			break;
		case 'L':
			isPaused = true;
			Sleep(200); // sleep to wait for the game loop to draw properly
			setCursorVisible(true);
			hideInstruction();
			gotoXY(20, 6*LANE_SIZE + 3);
			try {
				std::cout << "Pls enter the path to load: ";
				getline(std::cin, path);
				loadGame(path);
			}
			catch (std::string message) {
				gotoXY(20, 6 * LANE_SIZE + 3);
				std::cout << message << "                             ";
				setCursorVisible(false);
				Sleep(2000);
			}
			setCursorVisible(false);
			system("cls");
			isPaused = false;
			break;
		case 'X':
			isPaused = true;
			Sleep(200);
			setCursorVisible(true);
			hideInstruction();
			gotoXY(20, 6 * LANE_SIZE + 3);
			try {
				std::cout << "Pls enter the path to save: ";
				getline(std::cin, path);
				saveGame(path);
			}
			catch (std::string message) {
				gotoXY(20, 6 * LANE_SIZE + 3);
				std::cout << message << "                             ";
				setCursorVisible(false);
				Sleep(2000);
			}
			setCursorVisible(false);
			system("cls");
			isPaused = false;
			break;
		case ESC:
			exitGame();
		}
	}
}

void Game::handleMovementInput() {
	bool blockUp = false;
	bool blockDown = false;
	while (isRunning) {
		if (isPaused)
		continue;
		if (person.isDead)
			continue;
		bool left = (GetKeyState('A') | GetKeyState('a')) & 0x8000;
		bool right = (GetKeyState('D') | GetKeyState('d')) & 0x8000;
		if (!left && !right)
			person.setVel(0.0);
		else if (left && right)
			person.setVel(0.0);
		else if (left)
			person.setVel(-PERSON_SPEED);
		else if (right)
			person.setVel(PERSON_SPEED);
		bool up = (GetKeyState('W') | GetKeyState('w')) & 0x8000;
		bool down = (GetKeyState('S') | GetKeyState('s')) & 0x8000;
		if (up && !blockUp) {
			person.moveUp();
			blockUp = true;
		}
		else if (!up) {
			blockUp = false;
		}
		if (down && !blockDown) {
			person.moveDown();
			blockDown = true;
		}
		else if (!down) {
			blockDown = false;
		}
	}
}

void Game::run() {
	setValueBaseOnDifficulty();
	std::thread input(&Game::handleUserInput, this);
	std::thread movement(&Game::handleMovementInput, this);
	while (isRunning) {
		double timeElapsed = clock() - gameClock;
		gameClock = clock();
		if (!isPaused) {
			std::string fps = std::string("FPS: ") + std::to_string(1000.0 / timeElapsed);
			SetConsoleTitle(fps.c_str());
			update(timeElapsed);
			bool win = checkWin();
			render();
			if (win) {
				Sleep(1000);
				system("cls");
				reset(++level);
				resume();
			}
			if (timeElapsed < 20)
				Sleep(20);
		}
	}
	movement.join();
	input.join();
}

void Game::pause() {
	isPaused = true;
}

void Game::resume() {
	isPaused = false;
}

void Game::exitGame() {
	isRunning = false;
	exit(0);
}

void Game::update(double deltaTime) {
	// update traffic light
	trafficLightTime += deltaTime;
	if (trafficLightIsRed && trafficLightTime > RED_LIGHT_TIME) {
		trafficLightTime -= RED_LIGHT_TIME;
		trafficLightIsRed = !trafficLightIsRed;
	}	
	else if (!trafficLightIsRed && trafficLightTime > GREEN_LIGHT_TIME) {
		trafficLightTime -= GREEN_LIGHT_TIME;
		trafficLightIsRed = !trafficLightIsRed;
	}
	// update person
	if (!person.isDead)
		person.update(deltaTime);
	person.isDead = person.isDead || checkCollision();
	GAME_IS_OVER = person.isDead;
	// create ambulance
	if (person.isDead && ambulance.getPositionY() < 0) {
		// spawn ambulance
		if (person.getPositionY() == 2 * LANE_SIZE || person.getPositionY() == 4 * LANE_SIZE) {
			ambulance.setPosition(-23, person.getPositionY());
			ambulance.setVel(0.01);
		}
		else {
			ambulance.setPosition(WIDTH, person.getPositionY());
			ambulance.setVel(-0.01);
		}
	}
	// update ambulance
	if (!person.collide(ambulance))
		ambulance.update(deltaTime);
	// update random bird
	//randomBird.update(deltaTime);
	// update other obstacles
	if (!trafficLightIsRed || GAME_IS_OVER) {
		for (auto &car : cars)
			car.update(deltaTime);
		for (auto &truck : trucks)
			truck.update(deltaTime);
	}
	for (auto &bird : birds)
		bird.update(deltaTime);
	for (auto &dino : dinos)
		dino.update(deltaTime);
}

void Game::reset(int level) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	system("cls");
	if (sound) {
		PlaySound("Resource\\the-legend-of-zelda-overworld.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	this->level = level;
	person.isDead = false;
	trafficLightIsRed = false;
	gameClock = clock();
	trafficLightTime = 0;
	//randomBird.setPosition(-100, -HEIGHT);
	ambulance.setPosition(-100, -100);
	person.setPosition(((WIDTH / 2) / LANE_SIZE)*LANE_SIZE, LANE_SIZE * 5);
	cars.resize((level < MAX_CARS) ? level : MAX_CARS);
	trucks.resize((level < MAX_TRUCK) ? level : MAX_TRUCK);
	dinos.resize((level < MAX_DINO) ? level : MAX_DINO);
	birds.resize((level < MAX_BIRD) ? level : MAX_BIRD);
	for (auto &car : cars) {
		car.setPositionX(random(0, WIDTH / DISTANCE_BETWEEN_CARS + 1)*DISTANCE_BETWEEN_CARS);
		car.setVel(OBSTACLE_BASE_SPEED + OBSTACLE_SPEED_SCALE*level);
	}
	for (auto &truck : trucks) {
		truck.setPositionX(random(0, WIDTH / DISTANCE_BETWEEN_TRUCKS + 1)*DISTANCE_BETWEEN_TRUCKS);
		truck.setVel(-OBSTACLE_BASE_SPEED - OBSTACLE_SPEED_SCALE*level);
	}
	for (auto &dino : dinos) {
		dino.setPositionX(random(0, WIDTH / DISTANCE_BETWEEN_DINOS + 1)*DISTANCE_BETWEEN_DINOS);
		dino.setVel(OBSTACLE_BASE_SPEED + OBSTACLE_SPEED_SCALE*level);
	}
	for (auto &bird : birds) {
		bird.setPositionX(random(0, WIDTH / DISTANCE_BETWEEN_BIRDS + 1)*DISTANCE_BETWEEN_BIRDS);
		bird.setVel(-OBSTACLE_BASE_SPEED - OBSTACLE_SPEED_SCALE*level);
	}
}

void Game::render()  {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (checkWin()) {
		buffer.draw("You have pased level " + std::to_string(level), 48, 6 * LANE_SIZE - 1);
	}
	drawLanes();
	if (person.isDead)
		drawLosingOptions();
	if (!person.isDead && !checkWin())
		printInstruction();
	person.draw(buffer);
	for (const auto &car : cars)
		car.draw(buffer);
	for (const auto &truck : trucks)
		truck.draw(buffer);
	for (const auto &bird : birds)
		bird.draw(buffer);
	for (const auto &dino : dinos)
		dino.draw(buffer);
	//randomBird.draw(buffer);
	ambulance.draw(buffer);
	buffer.display();
	if (!GAME_IS_OVER)
		drawTrafficLight();
}

void Game::saveGame(std::string path) const {
	std::ofstream fout;
	fout.open(path.c_str(), std::ios::binary);
	if (!fout.is_open()) {
		throw std::string("Cannot save file ") + path;
	}
	// save difficulty
	fout.write((char*)&difficulty, sizeof(difficulty));
	// save the level
	fout.write((char*)&level, sizeof(level));
	// save the person position
	person.writeFile(fout);
	// save the cars' position
	size_t numCars = cars.size();
	fout.write((char*)&numCars, sizeof(numCars));
	for (const auto &car : cars) {
		car.writeFile(fout);
	}
	// truck
	size_t numTrucks = trucks.size();
	fout.write((char*)&numTrucks, sizeof(numTrucks));
	for (const auto &truck : trucks) {
		truck.writeFile(fout);
	}
	// dino
	size_t numDinos = dinos.size();
	fout.write((char*)&numDinos, sizeof(numDinos));
	for (const auto &dino : dinos) {
		dino.writeFile(fout);
	}
	// bird
	size_t numBirds = birds.size();
	fout.write((char*)&numBirds, sizeof(numBirds));
	for (const auto &bird : birds) {
		bird.writeFile(fout);
	}
	// save the random bird
	//randomBird.writeFile(fout);
	// save ambulance
	ambulance.writeFile(fout);
	// save traffic light
	fout.write((char*)&trafficLightIsRed, sizeof(trafficLightIsRed));
	fout.write((char*)&trafficLightTime, sizeof(trafficLightTime));
	// save person state
	fout.write((char*)&person.isDead, sizeof(person.isDead));
	fout.close();
}

void Game::loadGame(std::string path) {
	std::ifstream fin;
	fin.open(path.c_str(), std::ios::binary);
	if (!fin.is_open())
		throw std::string("Cannot load file ") + path;
	fin.read((char*)&difficulty, sizeof(difficulty));
	setValueBaseOnDifficulty();
	fin.read((char*)&level, sizeof(level));
	reset(level);
	person.readFile(fin);
	size_t n;
	// read cars's position
	fin.read((char*)&n, sizeof(n));
	cars.resize(n);
	for (auto &car : cars) {
		car.readFile(fin);
	}
	// truck
	fin.read((char*)&n, sizeof(n));
	trucks.resize(n);
	for (auto &truck : trucks) {
		truck.readFile(fin);
	}
	// dino
	fin.read((char*)&n, sizeof(n));
	dinos.resize(n);
	for (auto &dino : dinos) {
		dino.readFile(fin);
	}
	// bird
	fin.read((char*)&n, sizeof(n));
	birds.resize(n);
	for (auto &bird : birds) {
		bird.readFile(fin);
	}
	// load the random bird
	//randomBird.readFile(fin);
	// load ambulance
	ambulance.readFile(fin);
	// load traffic light
	fin.read((char*)&trafficLightIsRed, sizeof(trafficLightIsRed));
	fin.read((char*)&trafficLightTime, sizeof(trafficLightTime));
	// load player state
	fin.read((char*)&person.isDead, sizeof(person.isDead));
	fin.close();
}

bool Game::checkCollision() const {
	for (const auto &car : cars)
		if (person.collide(car)) {
			if (sound) {
				PlaySound("Resource\\Merged_car_ambul.wav", NULL, SND_ASYNC);
			}
			return true;
		}
	for (const auto &truck : trucks)
		if (person.collide(truck)) {
			if (sound) {
				PlaySound("Resource\\Merged_truck_ambul.wav", NULL, SND_ASYNC);
			}
			return true;
		}
	for (const auto &dino : dinos)
		if (person.collide(dino)) {
			if (sound) {
				PlaySound("Resource\\Merged_dino_ambul.wav", NULL, SND_ASYNC);
			}
			return true;
		}
	for (const auto &bird : birds)
		if (person.collide(bird)) {
			if (sound) {
				PlaySound("Resource\\Merged_bird_ambul.wav", NULL, SND_ASYNC);
			}
			return true;
		}
	return false;
}

bool Game::checkWin() const {
	return person.getPositionY() == 0;
}

void Game::setValueBaseOnDifficulty() {
	switch (difficulty) {
	case 0:
		OBSTACLE_BASE_SPEED = 0.007;
		OBSTACLE_SPEED_SCALE = 0.001;
		RED_LIGHT_TIME = 2000;
		GREEN_LIGHT_TIME = 3000;
		break;
	case 1:
		OBSTACLE_BASE_SPEED = 0.01;
		OBSTACLE_SPEED_SCALE = 0.002;
		RED_LIGHT_TIME = 1300;
		GREEN_LIGHT_TIME = 3000;
		break;
	case 2:
		OBSTACLE_BASE_SPEED = 0.02;
		OBSTACLE_SPEED_SCALE = 0.003;
		RED_LIGHT_TIME = 1000;
		GREEN_LIGHT_TIME = 3000;
		break;
	}
}