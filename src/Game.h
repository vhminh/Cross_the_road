#ifndef _GAME_H_
#define _GAME_H_
#include <ctime>
#include "Person.h"
#include "Buffer.h"
#include "Obstacle.h"
#include <string>
#include <vector>

class Game {
public:
	Game();
	void run();
	void loadGame(std::string path);
	void saveGame(std::string path) const;
	void pause();
	void resume();
	void exitGame();
private:
	clock_t gameClock;
	Person person;
	std::vector<Car> cars;
	std::vector<Truck> trucks;
	std::vector<Dinosaur> dinos;
	std::vector<Bird> birds;
	Ambulance ambulance;
	//RandomBird randomBird;
	Buffer buffer;
	bool isPaused;
	bool isRunning;
	int level;
	bool trafficLightIsRed;
	double trafficLightTime;
private:
	void handleUserInput(); // read the input from keyboard and process
	void handleMovementInput();
	void update(double deltaTime); // update new position of cars, trucks, bird and dinos
	bool checkCollision() const;
	bool checkWin() const;
	void render();
	void setValueBaseOnDifficulty();
private:
	void reset(int level);
	void drawLanes();
	void drawTrafficLight();
	void drawLosingOptions();
	void printInstruction();
	void hideInstruction();
};

#endif